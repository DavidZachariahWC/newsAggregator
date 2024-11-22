#ifndef STOPWORDS_H
#define STOPWORDS_H

#include <string>
#include <unordered_set>

// The StopWords class is responsible for managing a collection of stop words
// (commonly used words like "the", "is", "and") that are excluded during text processing.
class StopWords {
public:
    // Constructor initializes the stopWordsSet with a default list of common stop words
    StopWords();

    // Checks if a given word is a stop word
    // The comparison is case-insensitive
    bool isStopWord(const std::string& word) const;

private:
    std::unordered_set<std::string> stopWordsSet; // Stores the stop words for quick lookup

    // Loads a default set of stop words into the stopWordsSet
    void loadDefaultStopWords();
};

#endif
