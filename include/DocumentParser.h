#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <string>
#include <vector>
#include <memory>
#include "rapidjson/document.h"
#include "Document.h"
#include "StopWords.h"
#include "Stemmer.h"

class DocumentParser {
public:
    DocumentParser();

    // Parse a single document
    std::unique_ptr<Document> parseDocument(const std::string& filePath);
    
    // Parse all documents in a directory
    std::vector<std::unique_ptr<Document>> parseDirectory(const std::string& directoryPath);

    // Process text: remove stopwords and apply stemming
    std::string processText(const std::string& text);

private:
    StopWords stopWords;
    Stemmer stemmer;

    // Helper function to extract array from JSON
    std::vector<std::string> extractJsonArray(const rapidjson::Value& array);
    
    // Helper function to clean and normalize text
    std::string cleanText(const std::string& text);
};

#endif 