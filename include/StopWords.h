#ifndef STOPWORDS_H
#define STOPWORDS_H

#include <string>
#include <unordered_set>

// StopWords class for managing a set of stop words and checking if a word is a stop word
class StopWords {
public:
    StopWords(); // Constructor to initialize the stop words set
    
    // Checks if a given word is a stop word
    bool isStopWord(const std::string& word) const;

private:
    std::unordered_set<std::string> stopWordsSet; // Stores the set of stop words
    
    // Loads a default list of stop words into the stopWordsSet
    void loadDefaultStopWords();
};

#endif
