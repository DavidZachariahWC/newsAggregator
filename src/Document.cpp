#include "Document.h"
#include <sstream>
#include <algorithm>

// Default constructor
Document::Document() {}

// Constructor to initialize a Document with its file path
Document::Document(const std::string& filePath) : filePath(filePath) {}

// Retrieves the frequency of a specific term in the document
int Document::getTermFrequency(const std::string& term) const {
    auto it = termFrequencies.find(term); // Search for the term in the frequency map
    if (it != termFrequencies.end()) {
        return it->second; // Return the frequency if found
    }
    return 0; // Return 0 if the term is not present
}

// Sets the original text of the document and processes term frequencies
void Document::setText(const std::string& text) {
    this->originalText = text;  // Store the unprocessed original text
    this->text = text;          // Initialize the text field for further processing

    // Tokenize the text and calculate term frequencies
    std::istringstream iss(text);
    std::string word;
    termFrequencies.clear(); // Clear any previous frequency data

    while (iss >> word) {
        // Convert each word to lowercase for consistent, case-insensitive comparison
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        termFrequencies[word]++; // Increment frequency count for the word
    }
}

// Sets the processed text of the document (e.g., after stopword removal and stemming)
void Document::setProcessedText(const std::string& processedText) {
    this->text = processedText; // Update the text field with processed content
}

// Returns the original text of the document for display purposes
std::string Document::getText() const {
    return originalText; // Return the unprocessed original text
}

// Returns the processed text of the document for indexing and searching
std::string Document::getProcessedText() const {
    return text; // Return the processed text
}
