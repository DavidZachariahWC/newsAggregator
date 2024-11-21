#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "AVLTree.h"
#include "Document.h"

class IndexHandler {
public:
    IndexHandler();

    // Add a document to all indices
    void addDocument(const std::unique_ptr<Document>& doc);

    // Save/load indices
    void saveIndices(const std::string& filePath);
    void loadIndices(const std::string& filePath);

    // Search functions
    std::vector<std::shared_ptr<Document>> search(const std::string& term) const;
    std::vector<std::shared_ptr<Document>> searchOrganization(const std::string& org) const;
    std::vector<std::shared_ptr<Document>> searchPerson(const std::string& person) const;

    // Get relevant documents for multiple terms
    std::vector<std::shared_ptr<Document>> getRelevantDocuments(
        const std::vector<std::string>& terms,
        const std::vector<std::string>& excludedTerms,
        const std::vector<std::string>& organizations,
        const std::vector<std::string>& persons) const;

private:
    // AVL Trees for different indices
    AVLTree<std::string, std::vector<std::shared_ptr<Document>>> termIndex;
    AVLTree<std::string, std::vector<std::shared_ptr<Document>>> orgIndex;
    AVLTree<std::string, std::vector<std::shared_ptr<Document>>> personIndex;

    // Store documents to maintain their lifetime
    std::unordered_map<std::string, std::shared_ptr<Document>> documentStore;

    // Helper functions
    void addToIndex(const std::string& key, 
                   const std::shared_ptr<Document>& doc,
                   AVLTree<std::string, std::vector<std::shared_ptr<Document>>>& index);
                   
    // Calculate TF-IDF score for ranking
    double calculateTfIdf(const std::string& term, 
                         const std::shared_ptr<Document>& doc,
                         int totalDocs) const;
};

#endif 