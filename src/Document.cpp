#include "Document.h"
#include <sstream>
#include <algorithm>

Document::Document() {}

Document::Document(const std::string& filePath) : filePath(filePath) {}

int Document::getTermFrequency(const std::string& term) const {
    auto it = termFrequencies.find(term);
    if (it != termFrequencies.end()) {
        return it->second;
    }
    return 0;
}

void Document::setText(const std::string& text) {
    this->originalText = text;  // Store original text
    this->text = text;         // This will be processed by DocumentParser
    
    // Calculate term frequencies
    std::istringstream iss(text);
    std::string word;
    
    termFrequencies.clear();
    while (iss >> word) {
        // Convert to lowercase for case-insensitive comparison
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        termFrequencies[word]++;
    }
}

void Document::setProcessedText(const std::string& processedText) {
    this->text = processedText;
}

std::string Document::getText() const {
    return originalText;  // Return original text for display
}

std::string Document::getProcessedText() const {
    return text;  // Return processed text for searching
} 