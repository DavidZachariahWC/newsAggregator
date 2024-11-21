#include "StopWords.h"
#include <algorithm>

StopWords::StopWords() {
    loadDefaultStopWords();
}

bool StopWords::isStopWord(const std::string& word) const {
    // Convert word to lowercase for comparison
    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
    return stopWordsSet.find(lowerWord) != stopWordsSet.end();
}

void StopWords::loadDefaultStopWords() {
    // Common English stop words
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

    for (const auto& word : defaultStopWords) {
        stopWordsSet.insert(word);
    }
} 