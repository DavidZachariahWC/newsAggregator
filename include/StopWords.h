#ifndef STOPWORDS_H
#define STOPWORDS_H

#include <string>
#include <unordered_set>

class StopWords {
public:
    StopWords();
    
    bool isStopWord(const std::string& word) const;

private:
    std::unordered_set<std::string> stopWordsSet;
    void loadDefaultStopWords();
};

#endif 