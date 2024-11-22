#include "Document.h"
#include <sstream>
#include <algorithm>

// Default constructor
Document::Document() {}

// Constructor that initializes the Document with a file path
Document::Document(const std::string& filePath) : filePath(filePath) {}

// Get the frequency of a specific term in the document
int Document::getTermFrequency(const std::string& term) const {
    // Search for the term in the term frequency map
    auto it = termFrequencies.find(term);
    if (it != termFrequencies.end()) {
        return it->second; // Return the frequency if the term exists
    }
    return 0; // Return 0 if the term is not found
}

// Set the text for the document and calculate term frequencies
void Document::setText(const std::string& text) {
    this->originalText = text;  // Store the original text (unaltered)
    this->text = text;         // Set the text to be processed
    
    // Calculate term frequencies by breaking the text into words
    std::istringstream iss(text);
    std::string word;
    
    termFrequencies.clear(); // Clear previous term frequencies
    while (iss >> word) {
        // Convert the word to lowercase for case-insensitive processing
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        termFrequencies[word]++; // Increment the count for the word
    }
}

// Set the processed text (typically after some external processing like stemming)
void Document::setProcessedText(const std::string& processedText) {
    this->text = processedText; // Update the text with the processed version
}

// Get the original text of the document
std::string Document::getText() const {
    return originalText;  // Return the original, unprocessed text
}

// Get the processed text of the document
std::string Document::getProcessedText() const {
    return text;  // Return the processed version of the text
}
