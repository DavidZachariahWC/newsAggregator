#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <string>
#include <vector>
#include <memory>
#include "IndexHandler.h"
#include "Document.h"
#include "Stemmer.h"

// QueryProcessor class for parsing and processing user queries in the search engine
class QueryProcessor {
public:
    // Constructor initializes with a reference to the IndexHandler
    QueryProcessor(IndexHandler* indexHandler);

    // Processes a query string and retrieves matching documents
    std::vector<std::shared_ptr<Document>> processQuery(const std::string& queryString);

    // Displays query results to the console
    void displayResults(const std::vector<std::shared_ptr<Document>>& results);
    
    // Displays the full content of a selected document
    void displayDocument(const std::shared_ptr<Document>& doc);

private:
    IndexHandler* indexHandler; // Pointer to the index handler for querying

    // Query components extracted from the query string
    std::vector<std::string> terms;           // Terms included in the query
    std::vector<std::string> excludedTerms;   // Terms to exclude from results
    std::vector<std::string> organizations;  // Organization-specific terms
    std::vector<std::string> persons;        // Person-specific terms

    // Parses the query string into components such as terms and filters
    void parseQuery(const std::string& queryString);

    // Clears stored query components to handle new queries
    void clearQueryComponents();

    Stemmer stemmer; // Instance of the Stemmer for stemming terms
};

#endif
