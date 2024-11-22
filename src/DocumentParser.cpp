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

namespace fs = std::filesystem;

// Default constructor
DocumentParser::DocumentParser() {}

// Parses a single document from a JSON file
std::unique_ptr<Document> DocumentParser::parseDocument(const std::string& filePath) {
    // Open the file
    FILE* fp = fopen(filePath.c_str(), "rb");
    if (!fp) {
        return nullptr; // Return null if the file cannot be opened
    }

    // Buffer for reading the file
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    
    // Parse JSON content
    rapidjson::Document jsonDoc;
    jsonDoc.ParseStream(is);
    fclose(fp); // Close the file after reading

    if (jsonDoc.HasParseError()) {
        return nullptr; // Return null if JSON parsing fails
    }

    // Create a new Document object
    auto doc = std::make_unique<Document>(filePath);

    // Extract and set document metadata if available in JSON
    if (jsonDoc.HasMember("title") && jsonDoc["title"].IsString()) {
        doc->setTitle(jsonDoc["title"].GetString());
    }
    if (jsonDoc.HasMember("publication") && jsonDoc["publication"].IsString()) {
        doc->setPublication(jsonDoc["publication"].GetString());
    }
    if (jsonDoc.HasMember("date_published") && jsonDoc["date_published"].IsString()) {
        doc->setDatePublished(jsonDoc["date_published"].GetString());
    }

    // Extract and process the document's main text
    if (jsonDoc.HasMember("text") && jsonDoc["text"].IsString()) {
        std::string originalText = jsonDoc["text"].GetString();
        doc->setText(originalText); // Store the original text
        std::string processedText = processText(originalText); // Process text
        doc->setProcessedText(processedText); // Store processed text
    }

    // Extract and set additional metadata arrays
    if (jsonDoc.HasMember("authors") && jsonDoc["authors"].IsArray()) {
        doc->setAuthors(extractJsonArray(jsonDoc["authors"]));
    }
    if (jsonDoc.HasMember("organizations") && jsonDoc["organizations"].IsArray()) {
        doc->setOrganizations(extractJsonArray(jsonDoc["organizations"]));
    }
    if (jsonDoc.HasMember("persons") && jsonDoc["persons"].IsArray()) {
        doc->setPersons(extractJsonArray(jsonDoc["persons"]));
    }

    return doc; // Return the populated Document object
}

// Parses all JSON files in a directory recursively
std::vector<std::unique_ptr<Document>> DocumentParser::parseDirectory(const std::string& directoryPath) {
    std::vector<std::unique_ptr<Document>> documents;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            // Process only JSON files
            if (entry.is_regular_file() && entry.path().extension() == ".json") {
                if (auto doc = parseDocument(entry.path().string())) {
                    documents.push_back(std::move(doc)); // Add parsed document to the list
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        // Ignore filesystem errors silently
    }

    return documents; // Return the list of parsed documents
}

// Processes text by cleaning, removing stopwords, and applying stemming
std::string DocumentParser::processText(const std::string& text) {
    std::string cleaned = cleanText(text); // Clean raw text
    std::istringstream iss(cleaned);
    std::ostringstream oss;
    std::string word;

    while (iss >> word) {
        // Convert to lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Skip stopwords
        if (stopWords.isStopWord(word)) {
            continue;
        }

        // Apply stemming
        std::string stemmed = stemmer.stemWord(word);
        word = stemmed;

        // Append to the processed text
        oss << word << " ";
    }

    return oss.str(); // Return processed text
}

// Extracts an array of strings from a JSON array
std::vector<std::string> DocumentParser::extractJsonArray(const rapidjson::Value& array) {
    std::vector<std::string> result;
    for (const auto& item : array.GetArray()) {
        if (item.IsString()) {
            result.push_back(item.GetString()); // Add each string to the result vector
        }
    }
    return result;
}

// Cleans raw text by removing punctuation and normalizing spaces
std::string DocumentParser::cleanText(const std::string& text) {
    std::string cleaned;
    cleaned.reserve(text.length()); // Reserve space for efficiency

    for (char c : text) {
        if (std::ispunct(c)) {
            cleaned += ' '; // Replace punctuation with spaces
        } else if (std::isalnum(c) || std::isspace(c)) {
            cleaned += c; // Retain alphanumeric characters and spaces
        }
    }

    return cleaned; // Return cleaned text
}
