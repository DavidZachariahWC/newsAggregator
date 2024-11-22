#include "StopWords.h"
#include <algorithm>

// Constructor for the StopWords class
StopWords::StopWords() {
    loadDefaultStopWords(); // Load a predefined list of common English stop words
}

// Checks if a given word is a stop word
bool StopWords::isStopWord(const std::string& word) const {
    // Convert the word to lowercase to ensure case-insensitive comparison
    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
    
    // Check if the lowercase word exists in the stop words set
    return stopWordsSet.find(lowerWord) != stopWordsSet.end();
}

// Loads a predefined list of default stop words into the stopWordsSet
void StopWords::loadDefaultStopWords() {
    // Array of common English stop words
    const char* defaultStopWords[] = {
        "a", "an", "and", "are", "as", "at", "be", "by", "for", "from",
        "has", "he", "in", "is", "it", "its", "of", "on", "that", "the",
        "to", "was", "were", "will", "with", "the", "this", "but", "they",
        "have", "had", "what", "when", "where", "who", "which", "why", "how",
        "all", "any", "both", "each", "few", "more", "most", "other", "some",
        "such", "no", "nor", "not", "only", "own", "same", "so", "than",
        "too", "very", "can", "will", "just", "should", "now", "i", "you",
        "your", "we", "my", "me", "her", "his", "their", "our", "us", "am",
        "been", "being", "do", "does", "did", "doing", "would", "could",
        "might", "must", "shall", "into", "if", "then", "else", "about"
    };

    // Insert each stop word into the stopWordsSet for fast lookups
    for (const auto& word : defaultStopWords) {
        stopWordsSet.insert(word);
    }
}
