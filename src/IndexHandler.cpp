#include "IndexHandler.h"
#include <algorithm>
#include <cmath>
#include <sstream>

IndexHandler::IndexHandler() {}

void IndexHandler::addDocument(const std::unique_ptr<Document>& doc) {
    if (!doc) return;

    // Create shared_ptr and store it
    auto sharedDoc = std::make_shared<Document>(*doc);
    documentStore[doc->getFilePath()] = sharedDoc;

    // Show which file is being indexed
    std::cout << "Indexing: " << doc->getFilePath() << std::endl;

    // Index the terms in the document text - use processed text for indexing
    std::istringstream iss(doc->getProcessedText());
    std::string term;
    while (iss >> term) {
        addToIndex(term, sharedDoc, termIndex);
    }

    // Index organizations
    for (const auto& org : doc->getOrganizations()) {
        addToIndex(org, sharedDoc, orgIndex);
    }

    // Index persons
    for (const auto& person : doc->getPersons()) {
        addToIndex(person, sharedDoc, personIndex);
    }
}

void IndexHandler::addToIndex(const std::string& key, 
                            const std::shared_ptr<Document>& doc,
                            AVLTree<std::string, std::vector<std::shared_ptr<Document>>>& index) {
    std::vector<std::shared_ptr<Document>> docs;
    try {
        docs = index.find(key);
    } catch (...) {
        // Key doesn't exist yet, start with empty vector
    }
    docs.push_back(doc);
    index.insert(key, docs);
}

void IndexHandler::saveIndices(const std::string& filePath) {
    try {
        termIndex.saveToFile(filePath + "_terms.idx");
        orgIndex.saveToFile(filePath + "_orgs.idx");
        personIndex.saveToFile(filePath + "_persons.idx");
    } catch (const std::exception& e) {
        // Ignore errors during saving
    }
}

void IndexHandler::loadIndices(const std::string& filePath) {
    try {
        termIndex.loadFromFile(filePath + "_terms.idx");
        orgIndex.loadFromFile(filePath + "_orgs.idx");
        personIndex.loadFromFile(filePath + "_persons.idx");
    } catch (const std::exception& e) {
        // Ignore errors during loading
    }
}

std::vector<std::shared_ptr<Document>> IndexHandler::search(const std::string& term) const {
    return termIndex.find(term);
}

std::vector<std::shared_ptr<Document>> IndexHandler::searchOrganization(const std::string& org) const {
    return orgIndex.find(org);
}

std::vector<std::shared_ptr<Document>> IndexHandler::searchPerson(const std::string& person) const {
    return personIndex.find(person);
}

std::vector<std::shared_ptr<Document>> IndexHandler::getRelevantDocuments(
    const std::vector<std::string>& terms,
    const std::vector<std::string>& excludedTerms,
    const std::vector<std::string>& organizations,
    const std::vector<std::string>& persons) const {
    
    std::vector<std::shared_ptr<Document>> results;
    
    // If no terms provided, return empty result
    if (terms.empty() && organizations.empty() && persons.empty()) {
        return results;
    }

    // Get initial results from first term
    if (!terms.empty()) {
        results = search(terms[0]);
    } else if (!organizations.empty()) {
        results = searchOrganization(organizations[0]);
    } else {
        results = searchPerson(persons[0]);
    }

    // Intersect with other terms
    for (size_t i = 1; i < terms.size(); ++i) {
        auto termDocs = search(terms[i]);
        std::vector<std::shared_ptr<Document>> intersection;
        
        std::set_intersection(
            results.begin(), results.end(),
            termDocs.begin(), termDocs.end(),
            std::back_inserter(intersection)
        );
        
        results = intersection;
    }

    // Filter by organizations
    for (const auto& org : organizations) {
        auto orgDocs = searchOrganization(org);
        std::vector<std::shared_ptr<Document>> intersection;
        
        std::set_intersection(
            results.begin(), results.end(),
            orgDocs.begin(), orgDocs.end(),
            std::back_inserter(intersection)
        );
        
        results = intersection;
    }

    // Filter by persons
    for (const auto& person : persons) {
        auto personDocs = searchPerson(person);
        std::vector<std::shared_ptr<Document>> intersection;
        
        std::set_intersection(
            results.begin(), results.end(),
            personDocs.begin(), personDocs.end(),
            std::back_inserter(intersection)
        );
        
        results = intersection;
    }

    // Remove documents containing excluded terms
    for (const auto& excludedTerm : excludedTerms) {
        auto excludedDocs = search(excludedTerm);
        std::vector<std::shared_ptr<Document>> difference;
        
        std::set_difference(
            results.begin(), results.end(),
            excludedDocs.begin(), excludedDocs.end(),
            std::back_inserter(difference)
        );
        
        results = difference;
    }

    // Calculate TF-IDF scores and sort results
    std::vector<std::pair<double, std::shared_ptr<Document>>> scoredDocs;
    int totalDocs = documentStore.size();

    for (const auto& doc : results) {
        double score = 0.0;
        for (const auto& term : terms) {
            score += calculateTfIdf(term, doc, totalDocs);
        }
        scoredDocs.emplace_back(score, doc);
    }

    // Sort by score in descending order
    std::sort(scoredDocs.begin(), scoredDocs.end(),
        [](const auto& a, const auto& b) { return a.first > b.first; });

    // Extract sorted documents
    results.clear();
    for (const auto& [score, doc] : scoredDocs) {
        results.push_back(doc);
    }

    return results;
}

double IndexHandler::calculateTfIdf(const std::string& term, 
                                  const std::shared_ptr<Document>& doc,
                                  int totalDocs) const {
    // Calculate TF (term frequency)
    double tf = static_cast<double>(doc->getTermFrequency(term));
    
    // Calculate IDF (inverse document frequency)
    auto docsWithTerm = search(term);
    double idf = std::log(static_cast<double>(totalDocs) / 
                         (1 + static_cast<double>(docsWithTerm.size())));
    
    return tf * idf;
} 