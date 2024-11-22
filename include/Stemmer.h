#ifndef STEMMER_H
#define STEMMER_H

#include <string>

// Stemmer class implementing the Porter stemming algorithm for word reduction
class Stemmer {
public:
    Stemmer() = default; // Default constructor
    
    // Reduces a given word to its base/stem form using the Porter stemming algorithm
    std::string stemWord(const std::string& word);

private:
    // Helper function to check if a character at a given index is a consonant
    bool isConsonant(const std::string& str, int i);
    
    // Counts the number of consonant-vowel sequences in the word
    int countConsonantSequences(const std::string& str);
    
    // Checks if the word contains at least one vowel
    bool containsVowel(const std::string& str);
    
    // Checks if the word ends with a double consonant
    bool endsWithDoubleConsonant(const std::string& str);
    
    // Checks if the word ends in a consonant-vowel-consonant (CVC) sequence
    bool endsWithCVC(const std::string& str);

    // Porter stemming algorithm steps for word transformation
    std::string step1a(const std::string& str);
    std::string step1b(const std::string& str);
    std::string step1c(const std::string& str);
    std::string step2(const std::string& str);
    std::string step3(const std::string& str);
    std::string step4(const std::string& str);
    std::string step5(const std::string& str);

    // Helper function to replace specific suffixes in the word
    std::string replaceEnding(const std::string& str, const std::string& oldEnd, const std::string& newEnd);
};

#endif
