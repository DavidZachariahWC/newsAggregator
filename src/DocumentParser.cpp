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

DocumentParser::DocumentParser() {}

std::unique_ptr<Document> DocumentParser::parseDocument(const std::string& filePath) {
    // Open file
    FILE* fp = fopen(filePath.c_str(), "rb");
    if (!fp) {
        return nullptr;
    }

    // Read file into buffer
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    
    // Parse JSON
    rapidjson::Document jsonDoc;
    jsonDoc.ParseStream(is);
    fclose(fp);

    if (jsonDoc.HasParseError()) {
        return nullptr;
    }

    // Create document
    auto doc = std::make_unique<Document>(filePath);

    // Extract fields
    if (jsonDoc.HasMember("title") && jsonDoc["title"].IsString()) {
        doc->setTitle(jsonDoc["title"].GetString());
    }

    if (jsonDoc.HasMember("publication") && jsonDoc["publication"].IsString()) {
        doc->setPublication(jsonDoc["publication"].GetString());
    }

    if (jsonDoc.HasMember("date_published") && jsonDoc["date_published"].IsString()) {
        doc->setDatePublished(jsonDoc["date_published"].GetString());
    }

    if (jsonDoc.HasMember("text") && jsonDoc["text"].IsString()) {
        std::string originalText = jsonDoc["text"].GetString();
        doc->setText(originalText);  // Set original text first
        std::string processedText = processText(originalText);
        doc->setProcessedText(processedText);  // Then set processed text
    }

    // Extract arrays
    if (jsonDoc.HasMember("authors") && jsonDoc["authors"].IsArray()) {
        doc->setAuthors(extractJsonArray(jsonDoc["authors"]));
    }

    if (jsonDoc.HasMember("organizations") && jsonDoc["organizations"].IsArray()) {
        doc->setOrganizations(extractJsonArray(jsonDoc["organizations"]));
    }

    if (jsonDoc.HasMember("persons") && jsonDoc["persons"].IsArray()) {
        doc->setPersons(extractJsonArray(jsonDoc["persons"]));
    }

    return doc;
}

std::vector<std::unique_ptr<Document>> DocumentParser::parseDirectory(const std::string& directoryPath) {
    std::vector<std::unique_ptr<Document>> documents;
    
    try {
        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".json") {
                if (auto doc = parseDocument(entry.path().string())) {
                    documents.push_back(std::move(doc));
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        // Ignore filesystem errors
    }

    return documents;
}

std::string DocumentParser::processText(const std::string& text) {
    std::string cleaned = cleanText(text);
    std::istringstream iss(cleaned);
    std::ostringstream oss;
    std::string word;

    while (iss >> word) {
        // Convert to lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        // Skip if it's a stopword
        if (stopWords.isStopWord(word)) {
            continue;
        }

        // Apply stemming
        std::string stemmed = stemmer.stemWord(word);
        word = stemmed;
        
        oss << word << " ";
    }

    std::string result = oss.str();
    return result;
}

std::vector<std::string> DocumentParser::extractJsonArray(const rapidjson::Value& array) {
    std::vector<std::string> result;
    for (const auto& item : array.GetArray()) {
        if (item.IsString()) {
            result.push_back(item.GetString());
        }
    }
    return result;
}

std::string DocumentParser::cleanText(const std::string& text) {
    std::string cleaned;
    cleaned.reserve(text.length());
    
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
    
    return cleaned;
} 