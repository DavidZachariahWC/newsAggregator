#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "AVLTree.h"
#include "Document.h"

// The IndexHandler class manages indexing, searching, and ranking of documents.
// It uses AVL trees for efficient storage and retrieval of terms, organizations, and persons.
class IndexHandler {
public:
    // Constructor initializes the IndexHandler
    IndexHandler();

    // Adds a document to all relevant indices (terms, organizations, persons)
    void addDocument(const std::unique_ptr<Document>& doc);

    // Saves all indices to a specified file
    void saveIndices(const std::string& filePath);

    // Loads indices from a specified file
    void loadIndices(const std::string& filePath);

    // Searches for documents containing a specific term
    std::vector<std::shared_ptr<Document>> search(const std::string& term) const;

    // Searches for documents associated with a specific organization
    std::vector<std::shared_ptr<Document>> searchOrganization(const std::string& org) const;

    // Searches for documents associated with a specific person
    std::vector<std::shared_ptr<Document>> searchPerson(const std::string& person) const;

    // Retrieves relevant documents based on multiple criteria such as terms, excluded terms,
    // organizations, and persons. Used for advanced search queries.
    std::vector<std::shared_ptr<Document>> getRelevantDocuments(
        const std::vector<std::string>& terms,
        const std::vector<std::string>& excludedTerms,
        const std::vector<std::string>& organizations,
        const std::vector<std::string>& persons) const;

private:
    // AVL Trees for indexing terms, organizations, and persons
    AVLTree<std::string, std::vector<std::shared_ptr<Document>>> termIndex; // Index for terms
    AVLTree<std::string, std::vector<std::shared_ptr<Document>>> orgIndex;  // Index for organizations
    AVLTree<std::string, std::vector<std::shared_ptr<Document>>> personIndex; // Index for persons

    // Stores all documents to maintain their lifetime and enable efficient retrieval
    std::unordered_map<std::string, std::shared_ptr<Document>> documentStore;

    // Helper function to add a document to a specific index (e.g., terms, organizations, or persons)
    void addToIndex(const std::string& key, 
                   const std::shared_ptr<Document>& doc,
                   AVLTree<std::string, std::vector<std::shared_ptr<Document>>>& index);
                   
    // Calculates the TF-IDF score for ranking documents based on a search term
    double calculateTfIdf(const std::string& term, 
                         const std::shared_ptr<Document>& doc,
                         int totalDocs) const;
};

#endif
