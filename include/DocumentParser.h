#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <string>
#include <vector>
#include <memory>
#include "rapidjson/document.h"
#include "Document.h"
#include "StopWords.h"
#include "Stemmer.h"

// The DocumentParser class is responsible for parsing documents and directories,
// processing their text, and preparing them for indexing and querying.
class DocumentParser {
public:
    // Constructor initializes the parser with default stopwords and stemmer
    DocumentParser();

    // Parses a single document from a given file path and returns it as a Document object
    std::unique_ptr<Document> parseDocument(const std::string& filePath);
    
    // Parses all documents in a specified directory and returns a vector of Document objects
    std::vector<std::unique_ptr<Document>> parseDirectory(const std::string& directoryPath);

    // Processes text by removing stopwords, normalizing case, and applying stemming
    std::string processText(const std::string& text);

private:
    StopWords stopWords; // Handles the removal of stopwords
    Stemmer stemmer; // Applies stemming to reduce words to their base forms

    // Extracts an array of strings from a JSON array (e.g., authors, organizations)
    std::vector<std::string> extractJsonArray(const rapidjson::Value& array);
    
    // Cleans text by removing punctuation, normalizing case, and handling special characters
    std::string cleanText(const std::string& text);
};

#endif
