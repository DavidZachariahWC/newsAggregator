#include "DocumentParser.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

// Namespace alias for easier usage
namespace fs = std::filesystem;

// Default constructor for DocumentParser
DocumentParser::DocumentParser() {}

// Parse a single document from a JSON file
std::unique_ptr<Document> DocumentParser::parseDocument(const std::string& filePath) {
    // Open the JSON file in binary read mode
    FILE* fp = fopen(filePath.c_str(), "rb");
    if (!fp) {
        return nullptr; // Return null if the file cannot be opened
    }

    // Read the file into a buffer for parsing
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    
    // Parse the JSON content
    rapidjson::Document jsonDoc;
    jsonDoc.ParseStream(is);
    fclose(fp); // Close the file after parsing

    if (jsonDoc.HasParseError()) {
        return nullptr; // Return null if parsing fails
    }

    // Create a new Document object
    auto doc = std::make_unique<Document>(filePath);

    // Extract and set the title if it exists in the JSON
    if (jsonDoc.HasMember("title") && jsonDoc["title"].IsString()) {
        doc->setTitle(jsonDoc["title"].GetString());
    }

    // Extract and set the publication field if it exists in the JSON
    if (jsonDoc.HasMember("publication") && jsonDoc["publication"].IsString()) {
        doc->setPublication(jsonDoc["publication"].GetString());
    }

    // Extract and set the date published if it exists in the JSON
    if (jsonDoc.HasMember("date_published") && jsonDoc["date_published"].IsString()) {
        doc->setDatePublished(jsonDoc["date_published"].GetString());
    }

    // Extract and process the text field if it exists in the JSON
    if (jsonDoc.HasMember("text") && jsonDoc["text"].IsString()) {
        std::string originalText = jsonDoc["text"].GetString();
        doc->setText(originalText); // Set the original text in the Document
        std::string processedText = processText(originalText);
        doc->setProcessedText(processedText); // Set the processed text
    }

    // Extract and set the authors if the field exists as an array
    if (jsonDoc.HasMember("authors") && jsonDoc["authors"].IsArray()) {
        doc->setAuthors(extractJsonArray(jsonDoc["authors"]));
    }

    // Extract and set the organizations if the field exists as an array
    if (jsonDoc.HasMember("organizations") && jsonDoc["organizations"].IsArray()) {
        doc->setOrganizations(extractJsonArray(jsonDoc["organizations"]));
    }

    // Extract and set the persons if the field exists as an array
    if (jsonDoc.HasMember("persons") && jsonDoc["persons"].IsArray()) {
        doc->setPersons(extractJsonArray(jsonDoc["persons"]));
    }

    return doc; // Return the created Document object
}

// Parse all JSON documents in a directory
std::vector<std::unique_ptr<Document>> DocumentParser::parseDirectory(const std::string& directoryPath) {
    std::vector<std::unique_ptr<Document>> documents;
    
    try {
        // Iterate through all files in the directory (recursively)
        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            // Only process regular files with a .json extension
            if (entry.is_regular_file() && entry.path().extension() == ".json") {
                if (auto doc = parseDocument(entry.path().string())) {
                    documents.push_back(std::move(doc)); // Add parsed document to the list
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        // Ignore filesystem errors (e.g., permission issues)
    }

    return documents; // Return the list of documents
}

// Process the text by cleaning, filtering, and transforming it
std::string DocumentParser::processText(const std::string& text) {
    std::string cleaned = cleanText(text); // Clean the text first
    std::istringstream iss(cleaned);
    std::ostringstream oss;
    std::string word;

    while (iss >> word) {
        // Convert the word to lowercase for consistency
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        // Skip stopwords using a predefined stop word list
        if (stopWords.isStopWord(word)) {
            continue;
        }

        // Apply stemming to the word to reduce it to its base form
        std::string stemmed = stemmer.stemWord(word);
        word = stemmed;
        
        oss << word << " "; // Add the processed word to the output stream
    }

    std::string result = oss.str();
    return result; // Return the fully processed text
}

// Extract a JSON array into a vector of strings
std::vector<std::string> DocumentParser::extractJsonArray(const rapidjson::Value& array) {
    std::vector<std::string> result;
    for (const auto& item : array.GetArray()) {
        if (item.IsString()) {
            result.push_back(item.GetString()); // Add each string to the result vector
        }
    }
    return result; // Return the extracted vector of strings
}

// Clean the text by removing punctuation and keeping alphanumeric characters
std::string DocumentParser::cleanText(const std::string& text) {
    std::string cleaned;
    cleaned.reserve(text.length()); // Preallocate memory for the cleaned string
    
    for (char c : text) {
        // Replace punctuation with spaces
        if (std::ispunct(c)) {
            cleaned += ' ';
        }
        // Keep alphanumeric characters and spaces
        else if (std::isalnum(c) || std::isspace(c)) {
            cleaned += c;
        }
    }
    
    return cleaned; // Return the cleaned text
}
