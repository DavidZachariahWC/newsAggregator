#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "AVLTree.h"
#include "Document.h"

// IndexHandler class for managing and querying indices for terms, organizations, and persons
class IndexHandler {
public:
    IndexHandler(); // Default constructor

    // Adds a document to all relevant indices (terms, organizations, persons)
    void addDocument(const std::unique_ptr<Document>& doc);

    // Saves all indices to a file for persistence
    void saveIndices(const std::string& filePath);

    // Loads all indices from a file
    void loadIndices(const std::string& filePath);

    // Searches for documents containing a specific term
    std::vector<std::shared_ptr<Document>> search(const std::string& term) const;

    // Searches for documents mentioning a specific organization
    std::vector<std::shared_ptr<Document>> searchOrganization(const std::string& org) const;

    // Searches for documents mentioning a specific person
    std::vector<std::shared_ptr<Document>> searchPerson(const std::string& person) const;

    // Retrieves documents relevant to multiple terms, excluding some terms, and filtered by organizations or persons
    std::vector<std::shared_ptr<Document>> getRelevantDocuments(
        const std::vector<std::string>& terms,
        const std::vector<std::string>& excludedTerms,
        const std::vector<std::string>& organizations,
        const std::vector<std::string>& persons) const;

private:
    // AVL Trees for indexing
    AVLTree<std::string, std::vector<std::shared_ptr<Document>>> termIndex;  // Index for terms
    AVLTree<std::string, std::vector<std::shared_ptr<Document>>> orgIndex;   // Index for organizations
    AVLTree<std::string, std::vector<std::shared_ptr<Document>>> personIndex; // Index for persons

    // Stores all documents to ensure their lifetime and provide unique access
    std::unordered_map<std::string, std::shared_ptr<Document>> documentStore;

    // Adds a document to a specific index (terms, organizations, or persons)
    void addToIndex(const std::string& key, 
                    const std::shared_ptr<Document>& doc,
                    AVLTree<std::string, std::vector<std::shared_ptr<Document>>>& index);

    // Calculates the TF-IDF score of a term in a document for ranking purposes
    double calculateTfIdf(const std::string& term, 
                          const std::shared_ptr<Document>& doc,
                          int totalDocs) const;
};

#endif
