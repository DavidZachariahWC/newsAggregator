#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <string>
#include <vector>
#include <memory>
#include "rapidjson/document.h"
#include "Document.h"
#include "StopWords.h"
#include "Stemmer.h"

// DocumentParser class for parsing, processing, and cleaning documents in the search engine
class DocumentParser {
public:
    DocumentParser(); // Default constructor

    // Parses a single document from a file and returns a Document object
    std::unique_ptr<Document> parseDocument(const std::string& filePath);

    // Parses all documents in a directory and returns a list of Document objects
    std::vector<std::unique_ptr<Document>> parseDirectory(const std::string& directoryPath);

    // Processes text by removing stopwords and applying stemming
    std::string processText(const std::string& text);

private:
    StopWords stopWords; // StopWords instance to manage and remove common words
    Stemmer stemmer;     // Stemmer instance to reduce words to their base forms

    // Extracts an array of strings from a JSON value
    std::vector<std::string> extractJsonArray(const rapidjson::Value& array);

    // Cleans and normalizes raw text, removing unwanted characters or formatting
    std::string cleanText(const std::string& text);
};

#endif
