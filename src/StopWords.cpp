#include "StopWords.h"
#include <algorithm>

// Constructor initializes the stopWordsSet with default stop words
StopWords::StopWords() {
    loadDefaultStopWords();
}

// Checks if a given word is a stop word
bool StopWords::isStopWord(const std::string& word) const {
    // Convert the word to lowercase for case-insensitive comparison
    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
    
    // Check if the word exists in the stopWordsSet
    return stopWordsSet.find(lowerWord) != stopWordsSet.end();
}

// Loads a default list of common English stop words into the set
void StopWords::loadDefaultStopWords() {
    // Common English stop words used for filtering uninformative words
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

    // Add each stop word to the set for efficient lookup
    for (const auto& word : defaultStopWords) {
        stopWordsSet.insert(word);
    }
}
