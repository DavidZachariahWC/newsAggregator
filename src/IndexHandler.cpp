#include "IndexHandler.h"
#include <algorithm>
#include <cmath>
#include <sstream>

// Default constructor
IndexHandler::IndexHandler() {}

// Adds a document to the indices (terms, organizations, persons)
void IndexHandler::addDocument(const std::unique_ptr<Document>& doc) {
    if (!doc) return; // Skip null documents

    // Convert to shared_ptr and store in documentStore
    auto sharedDoc = std::make_shared<Document>(*doc);
    documentStore[doc->getFilePath()] = sharedDoc;

    // Log the file being indexed
    std::cout << "Indexing: " << doc->getFilePath() << std::endl;

    // Index terms from processed text
    std::istringstream iss(doc->getProcessedText());
    std::string term;
    while (iss >> term) {
        addToIndex(term, sharedDoc, termIndex);
    }

    // Index associated organizations
    for (const auto& org : doc->getOrganizations()) {
        addToIndex(org, sharedDoc, orgIndex);
    }

    // Index associated persons
    for (const auto& person : doc->getPersons()) {
        addToIndex(person, sharedDoc, personIndex);
    }
}

// Adds a document to a specific index (term, organization, or person)
void IndexHandler::addToIndex(const std::string& key, 
                              const std::shared_ptr<Document>& doc,
                              AVLTree<std::string, std::vector<std::shared_ptr<Document>>>& index) {
    std::vector<std::shared_ptr<Document>> docs;
    try {
        docs = index.find(key); // Retrieve existing entries for the key
    } catch (...) {
        // If key doesn't exist, initialize with an empty vector
    }
    docs.push_back(doc); // Add the document to the list
    index.insert(key, docs); // Update the index
}

// Saves all indices to separate files for persistence
void IndexHandler::saveIndices(const std::string& filePath) {
    try {
        termIndex.saveToFile(filePath + "_terms.idx");
        orgIndex.saveToFile(filePath + "_orgs.idx");
        personIndex.saveToFile(filePath + "_persons.idx");
    } catch (const std::exception& e) {
        // Ignore errors during saving
    }
}

// Loads all indices from files
void IndexHandler::loadIndices(const std::string& filePath) {
    try {
        termIndex.loadFromFile(filePath + "_terms.idx");
        orgIndex.loadFromFile(filePath + "_orgs.idx");
        personIndex.loadFromFile(filePath + "_persons.idx");
    } catch (const std::exception& e) {
        // Ignore errors during loading
    }
}

// Searches for documents containing a specific term
std::vector<std::shared_ptr<Document>> IndexHandler::search(const std::string& term) const {
    return termIndex.find(term);
}

// Searches for documents mentioning a specific organization
std::vector<std::shared_ptr<Document>> IndexHandler::searchOrganization(const std::string& org) const {
    return orgIndex.find(org);
}

// Searches for documents mentioning a specific person
std::vector<std::shared_ptr<Document>> IndexHandler::searchPerson(const std::string& person) const {
    return personIndex.find(person);
}

// Retrieves relevant documents filtered by terms, organizations, and persons
std::vector<std::shared_ptr<Document>> IndexHandler::getRelevantDocuments(
    const std::vector<std::string>& terms,
    const std::vector<std::string>& excludedTerms,
    const std::vector<std::string>& organizations,
    const std::vector<std::string>& persons) const {

    std::vector<std::shared_ptr<Document>> results;

    // Return empty result if no filters are provided
    if (terms.empty() && organizations.empty() && persons.empty()) {
        return results;
    }

    // Get initial results from the first term or filter
    if (!terms.empty()) {
        results = search(terms[0]);
    } else if (!organizations.empty()) {
        results = searchOrganization(organizations[0]);
    } else {
        results = searchPerson(persons[0]);
    }

    // Intersect results with additional terms
    for (size_t i = 1; i < terms.size(); ++i) {
        auto termDocs = search(terms[i]);
        std::vector<std::shared_ptr<Document>> intersection;
        std::set_intersection(
            results.begin(), results.end(),
            termDocs.begin(), termDocs.end(),
            std::back_inserter(intersection));
        results = intersection;
    }

    // Filter results by organizations
    for (const auto& org : organizations) {
        auto orgDocs = searchOrganization(org);
        std::vector<std::shared_ptr<Document>> intersection;
        std::set_intersection(
            results.begin(), results.end(),
            orgDocs.begin(), orgDocs.end(),
            std::back_inserter(intersection));
        results = intersection;
    }

    // Filter results by persons
    for (const auto& person : persons) {
        auto personDocs = searchPerson(person);
        std::vector<std::shared_ptr<Document>> intersection;
        std::set_intersection(
            results.begin(), results.end(),
            personDocs.begin(), personDocs.end(),
            std::back_inserter(intersection));
        results = intersection;
    }

    // Exclude documents containing excluded terms
    for (const auto& excludedTerm : excludedTerms) {
        auto excludedDocs = search(excludedTerm);
        std::vector<std::shared_ptr<Document>> difference;
        std::set_difference(
            results.begin(), results.end(),
            excludedDocs.begin(), excludedDocs.end(),
            std::back_inserter(difference));
        results = difference;
    }

    // Rank results by TF-IDF scores
    std::vector<std::pair<double, std::shared_ptr<Document>>> scoredDocs;
    int totalDocs = documentStore.size();
    for (const auto& doc : results) {
        double score = 0.0;
        for (const auto& term : terms) {
            score += calculateTfIdf(term, doc, totalDocs);
        }
        scoredDocs.emplace_back(score, doc);
    }

    // Sort documents by descending score
    std::sort(scoredDocs.begin(), scoredDocs.end(),
        [](const auto& a, const auto& b) { return a.first > b.first; });

    // Extract sorted documents
    results.clear();
    for (const auto& [score, doc] : scoredDocs) {
        results.push_back(doc);
    }

    return results;
}

// Calculates the TF-IDF score for a term in a document
double IndexHandler::calculateTfIdf(const std::string& term, 
                                    const std::shared_ptr<Document>& doc,
                                    int totalDocs) const {
    double tf = static_cast<double>(doc->getTermFrequency(term)); // Term frequency
    auto docsWithTerm = search(term);
    double idf = std::log(static_cast<double>(totalDocs) / (1 + docsWithTerm.size())); // Inverse document frequency
    return tf * idf; // Return TF-IDF score
}
