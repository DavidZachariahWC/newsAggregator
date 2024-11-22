#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <string>
#include <vector>
#include <memory>
#include "IndexHandler.h"
#include "Document.h"
#include "Stemmer.h"

// The QueryProcessor class handles user queries, processes them, and retrieves matching documents.
// It interacts with the IndexHandler to perform searches and displays results to the console.
class QueryProcessor {
public:
    // Constructor that initializes the QueryProcessor with a reference to an IndexHandler
    QueryProcessor(IndexHandler* indexHandler);

    // Processes a query string, parses it into components, and retrieves matching documents
    std::vector<std::shared_ptr<Document>> processQuery(const std::string& queryString);

    // Displays a list of search results to the console
    void displayResults(const std::vector<std::shared_ptr<Document>>& results);

    // Displays the full details of a specific document
    void displayDocument(const std::shared_ptr<Document>& doc);

private:
    IndexHandler* indexHandler; // Pointer to the IndexHandler for performing searches

    // Query components parsed from the input query string
    std::vector<std::string> terms;           // Terms to include in the search
    std::vector<std::string> excludedTerms;   // Terms to exclude from the search
    std::vector<std::string> organizations;  // Organizations to include in the search
    std::vector<std::string> persons;        // Persons to include in the search

    // Parses a query string into its components (terms, excluded terms, organizations, and persons)
    void parseQuery(const std::string& queryString);

    // Clears previous query components to prepare for a new query
    void clearQueryComponents();

    Stemmer stemmer; // Stemmer for reducing words to their base forms
};

#endif
