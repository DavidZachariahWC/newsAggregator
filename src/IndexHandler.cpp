#include "IndexHandler.h"
#include <algorithm>
#include <cmath>
#include <sstream>

// Default constructor
IndexHandler::IndexHandler() {}

// Add a document to the index
void IndexHandler::addDocument(const std::unique_ptr<Document>& doc) {
    if (!doc) return; // Skip if the document is null

    // Convert unique_ptr to shared_ptr and store it in the documentStore
    auto sharedDoc = std::make_shared<Document>(*doc);
    documentStore[doc->getFilePath()] = sharedDoc;

    // Output the file path being indexed
    std::cout << "Indexing: " << doc->getFilePath() << std::endl;

    // Index terms from the processed text of the document
    std::istringstream iss(doc->getProcessedText());
    std::string term;
    while (iss >> term) {
        addToIndex(term, sharedDoc, termIndex); // Add term to the termIndex
    }

    // Index organizations
    for (const auto& org : doc->getOrganizations()) {
        addToIndex(org, sharedDoc, orgIndex); // Add organizations to the orgIndex
    }

    // Index persons
    for (const auto& person : doc->getPersons()) {
        addToIndex(person, sharedDoc, personIndex); // Add persons to the personIndex
    }
}

// Helper function to add a key and document to a specific index
void IndexHandler::addToIndex(const std::string& key, 
                            const std::shared_ptr<Document>& doc,
                            AVLTree<std::string, std::vector<std::shared_ptr<Document>>>& index) {
    std::vector<std::shared_ptr<Document>> docs;
    try {
        docs = index.find(key); // Attempt to find existing documents for the key
    } catch (...) {
        // If key doesn't exist, start with an empty vector
    }
    docs.push_back(doc); // Add the document to the vector
    index.insert(key, docs); // Insert or update the index with the new vector
}

// Save the indices to files
void IndexHandler::saveIndices(const std::string& filePath) {
    try {
        termIndex.saveToFile(filePath + "_terms.idx"); // Save termIndex to file
        orgIndex.saveToFile(filePath + "_orgs.idx");  // Save orgIndex to file
        personIndex.saveToFile(filePath + "_persons.idx"); // Save personIndex to file
    } catch (const std::exception& e) {
        // Ignore any errors that occur during saving
    }
}

// Load indices from files
void IndexHandler::loadIndices(const std::string& filePath) {
    try {
        termIndex.loadFromFile(filePath + "_terms.idx"); // Load termIndex from file
        orgIndex.loadFromFile(filePath + "_orgs.idx");  // Load orgIndex from file
        personIndex.loadFromFile(filePath + "_persons.idx"); // Load personIndex from file
    } catch (const std::exception& e) {
        // Ignore any errors that occur during loading
    }
}

// Search for documents matching a specific term
std::vector<std::shared_ptr<Document>> IndexHandler::search(const std::string& term) const {
    return termIndex.find(term); // Return documents associated with the term
}

// Search for documents matching a specific organization
std::vector<std::shared_ptr<Document>> IndexHandler::searchOrganization(const std::string& org) const {
    return orgIndex.find(org); // Return documents associated with the organization
}

// Search for documents matching a specific person
std::vector<std::shared_ptr<Document>> IndexHandler::searchPerson(const std::string& person) const {
    return personIndex.find(person); // Return documents associated with the person
}

// Get documents relevant to a combination of terms, organizations, and persons
std::vector<std::shared_ptr<Document>> IndexHandler::getRelevantDocuments(
    const std::vector<std::string>& terms,
    const std::vector<std::string>& excludedTerms,
    const std::vector<std::string>& organizations,
    const std::vector<std::string>& persons) const {
    
    std::vector<std::shared_ptr<Document>> results;
    
    // If no terms, organizations, or persons are provided, return an empty result
    if (terms.empty() && organizations.empty() && persons.empty()) {
        return results;
    }

    // Get initial results based on the first term, organization, or person
    if (!terms.empty()) {
        results = search(terms[0]); // Search by the first term
    } else if (!organizations.empty()) {
        results = searchOrganization(organizations[0]); // Search by the first organization
    } else {
        results = searchPerson(persons[0]); // Search by the first person
    }

    // Refine results by intersecting with other terms
    for (size_t i = 1; i < terms.size(); ++i) {
        auto termDocs = search(terms[i]); // Get documents for the term
        std::vector<std::shared_ptr<Document>> intersection;
        
        std::set_intersection(
            results.begin(), results.end(),
            termDocs.begin(), termDocs.end(),
            std::back_inserter(intersection)
        );
        
        results = intersection; // Update results with the intersection
    }

    // Filter results by organizations
    for (const auto& org : organizations) {
        auto orgDocs = searchOrganization(org); // Get documents for the organization
        std::vector<std::shared_ptr<Document>> intersection;
        
        std::set_intersection(
            results.begin(), results.end(),
            orgDocs.begin(), orgDocs.end(),
            std::back_inserter(intersection)
        );
        
        results = intersection; // Update results with the intersection
    }

    // Filter results by persons
    for (const auto& person : persons) {
        auto personDocs = searchPerson(person); // Get documents for the person
        std::vector<std::shared_ptr<Document>> intersection;
        
        std::set_intersection(
            results.begin(), results.end(),
            personDocs.begin(), personDocs.end(),
            std::back_inserter(intersection)
        );
        
        results = intersection; // Update results with the intersection
    }

    // Remove documents that contain excluded terms
    for (const auto& excludedTerm : excludedTerms) {
        auto excludedDocs = search(excludedTerm); // Get documents for the excluded term
        std::vector<std::shared_ptr<Document>> difference;
        
        std::set_difference(
            results.begin(), results.end(),
            excludedDocs.begin(), excludedDocs.end(),
            std::back_inserter(difference)
        );
        
        results = difference; // Update results with the difference
    }

    // Calculate TF-IDF scores for the remaining documents and sort them
    std::vector<std::pair<double, std::shared_ptr<Document>>> scoredDocs;
    int totalDocs = documentStore.size();

    for (const auto& doc : results) {
        double score = 0.0;
        for (const auto& term : terms) {
            score += calculateTfIdf(term, doc, totalDocs); // Calculate TF-IDF score for the term
        }
        scoredDocs.emplace_back(score, doc); // Pair the score with the document
    }

    // Sort the documents by their scores in descending order
    std::sort(scoredDocs.begin(), scoredDocs.end(),
        [](const auto& a, const auto& b) { return a.first > b.first; });

    // Extract the sorted documents into the result vector
    results.clear();
    for (const auto& [score, doc] : scoredDocs) {
        results.push_back(doc);
    }

    return results; // Return the sorted documents
}

// Calculate the TF-IDF score for a specific term in a document
double IndexHandler::calculateTfIdf(const std::string& term, 
                                  const std::shared_ptr<Document>& doc,
                                  int totalDocs) const {
    // Calculate term frequency (TF)
    double tf = static_cast<double>(doc->getTermFrequency(term));
    
    // Calculate inverse document frequency (IDF)
    auto docsWithTerm = search(term);
    double idf = std::log(static_cast<double>(totalDocs) / 
                         (1 + static_cast<double>(docsWithTerm.size()))); // Add 1 to avoid division by zero
    
    return tf * idf; // Return the TF-IDF score
}
