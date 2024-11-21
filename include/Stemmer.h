#ifndef STEMMER_H
#define STEMMER_H

#include <string>

class Stemmer {
public:
    Stemmer() = default;
    
    // Main stemming function
    std::string stemWord(const std::string& word);

private:
    // Helper functions for Porter stemming algorithm
    bool isConsonant(const std::string& str, int i);
    int countConsonantSequences(const std::string& str);
    bool containsVowel(const std::string& str);
    bool endsWithDoubleConsonant(const std::string& str);
    bool endsWithCVC(const std::string& str);
    
    // Step functions for Porter algorithm
    std::string step1a(const std::string& str);
    std::string step1b(const std::string& str);
    std::string step1c(const std::string& str);
    std::string step2(const std::string& str);
    std::string step3(const std::string& str);
    std::string step4(const std::string& str);
    std::string step5(const std::string& str);
    
    // Helper to replace endings
    std::string replaceEnding(const std::string& str, const std::string& oldEnd, const std::string& newEnd);
};

#endif 