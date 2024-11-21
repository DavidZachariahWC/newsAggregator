#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <string>
#include <vector>
#include <memory>
#include "IndexHandler.h"
#include "Document.h"
#include "Stemmer.h"

class QueryProcessor {
public:
    QueryProcessor(IndexHandler* indexHandler);

    // Process a query and return results
    std::vector<std::shared_ptr<Document>> processQuery(const std::string& queryString);

    // Display results to console
    void displayResults(const std::vector<std::shared_ptr<Document>>& results);
    void displayDocument(const std::shared_ptr<Document>& doc);

private:
    IndexHandler* indexHandler;

    // Query components
    std::vector<std::string> terms;
    std::vector<std::string> excludedTerms;
    std::vector<std::string> organizations;
    std::vector<std::string> persons;

    // Parse query string into components
    void parseQuery(const std::string& queryString);

    // Clear previous query components
    void clearQueryComponents();

    Stemmer stemmer;
};

#endif 