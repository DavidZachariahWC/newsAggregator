#ifndef STEMMER_H
#define STEMMER_H

#include <string>

// The Stemmer class implements the Porter stemming algorithm to reduce words to their base or root form.
// This is commonly used in text processing to normalize words for comparison and analysis.
class Stemmer {
public:
    Stemmer() = default; // Default constructor

    // Main function to stem a word using the Porter algorithm
    std::string stemWord(const std::string& word);

private:
    // Helper function to determine if a character at a given position is a consonant
    bool isConsonant(const std::string& str, int i);

    // Counts the number of consonant-vowel-consonant sequences in a word
    int countConsonantSequences(const std::string& str);

    // Checks if a word contains at least one vowel
    bool containsVowel(const std::string& str);

    // Checks if a word ends with a double consonant (e.g., "tt", "ss")
    bool endsWithDoubleConsonant(const std::string& str);

    // Checks if a word ends with a consonant-vowel-consonant (CVC) pattern
    bool endsWithCVC(const std::string& str);

    // Step functions for the different stages of the Porter stemming algorithm
    std::string step1a(const std::string& str); // Handles plurals and -ed, -ing suffixes
    std::string step1b(const std::string& str); // Further processing of -ed, -ing
    std::string step1c(const std::string& str); // Converts terminal "y" to "i" if applicable
    std::string step2(const std::string& str);  // Handles suffixes like -ational, -tional
    std::string step3(const std::string& str);  // Simplifies suffixes like -icate, -ative
    std::string step4(const std::string& str);  // Removes common suffixes like -ment, -ness
    std::string step5(const std::string& str);  // Final clean-up, e.g., removing terminal "e"

    // Replaces a specific ending of a word with a new ending if the old ending is present
    std::string replaceEnding(const std::string& str, const std::string& oldEnd, const std::string& newEnd);
};

#endif
