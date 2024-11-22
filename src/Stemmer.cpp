#include "Stemmer.h"
#include <algorithm>
#include <string>

// Helper function to check if a string ends with a specific suffix
bool ends_with(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) return false; // If the string is shorter than the suffix, return false
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0; // Compare the suffix
}

// Main function to apply stemming to a word using the Porter algorithm
std::string Stemmer::stemWord(const std::string& word) {
    if (word.length() <= 2) return word; // Skip words with 2 or fewer characters
    
    // Convert the word to lowercase for uniform processing
    std::string str = word;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    
    // Apply each step of the Porter stemming algorithm
    str = step1a(str);
    str = step1b(str);
    str = step1c(str);
    str = step2(str);
    str = step3(str);
    str = step4(str);
    str = step5(str);
    
    return str; // Return the stemmed word
}

// Determines whether a character in a string is a consonant
bool Stemmer::isConsonant(const std::string& str, int i) {
    char c = str[i];
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return false; // Vowels are not consonants
    if (c == 'y') {
        // 'y' is a consonant only if it follows a vowel
        return (i == 0) ? true : !isConsonant(str, i - 1);
    }
    return true; // All other characters are consonants
}

// Counts the number of consonant-vowel-consonant sequences in a word
int Stemmer::countConsonantSequences(const std::string& str) {
    int count = 0;
    bool inConsonant = false;
    for (size_t i = 0; i < str.length(); i++) {
        if (isConsonant(str, i)) {
            if (!inConsonant) { // Start a new consonant sequence
                count++;
                inConsonant = true;
            }
        } else {
            inConsonant = false; // End of a consonant sequence
        }
    }
    return count; // Return the total count
}

// Checks if the string contains at least one vowel
bool Stemmer::containsVowel(const std::string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!isConsonant(str, i)) return true; // Return true if a vowel is found
    }
    return false; // No vowels found
}

// Checks if a string ends with a double consonant (e.g., "tt", "ss")
bool Stemmer::endsWithDoubleConsonant(const std::string& str) {
    if (str.length() < 2) return false; // A double consonant requires at least 2 characters
    return (isConsonant(str, str.length() - 1) && 
            isConsonant(str, str.length() - 2) &&
            str[str.length() - 1] == str[str.length() - 2]); // Check if the last two characters are consonants and the same
}

// Checks if a string ends with a consonant-vowel-consonant (CVC) pattern
bool Stemmer::endsWithCVC(const std::string& str) {
    if (str.length() < 3) return false; // A CVC pattern requires at least 3 characters
    
    size_t last = str.length() - 1;
    char last_char = str[last];
    
    return (isConsonant(str, last - 2) &&
            !isConsonant(str, last - 1) &&
            isConsonant(str, last) &&
            last_char != 'w' && last_char != 'x' && last_char != 'y'); // Exclude "w", "x", "y" from being the last consonant
}

// Replaces the ending of a string if it matches a specified suffix
std::string Stemmer::replaceEnding(const std::string& str, 
                                 const std::string& oldEnd, 
                                 const std::string& newEnd) {
    if (str.length() < oldEnd.length()) return str; // Return the original string if it's shorter than the suffix
    
    std::string ending = str.substr(str.length() - oldEnd.length());
    if (ending == oldEnd) { // If the suffix matches, replace it
        return str.substr(0, str.length() - oldEnd.length()) + newEnd;
    }
    return str; // Return the original string if the suffix doesn't match
}

// Step 1a of the Porter stemming algorithm: Handle plurals and simple endings
std::string Stemmer::step1a(const std::string& str) {
    if (ends_with(str, "sses")) return replaceEnding(str, "sses", "ss");
    if (ends_with(str, "ies")) return replaceEnding(str, "ies", "i");
    if (ends_with(str, "ss")) return str; // "ss" remains unchanged
    if (ends_with(str, "s")) return replaceEnding(str, "s", ""); // Remove "s"
    return str;
}

// Step 1b of the Porter stemming algorithm: Handle past tense and participles
std::string Stemmer::step1b(const std::string& str) {
    if (ends_with(str, "eed")) {
        std::string stem = str.substr(0, str.length() - 3);
        if (countConsonantSequences(stem) > 0)
            return replaceEnding(str, "eed", "ee");
        return str;
    }
    
    if (ends_with(str, "ed")) {
        std::string stem = str.substr(0, str.length() - 2);
        if (containsVowel(stem))
            return replaceEnding(str, "ed", "");
    }
    
    if (ends_with(str, "ing")) {
        std::string stem = str.substr(0, str.length() - 3);
        if (containsVowel(stem))
            return replaceEnding(str, "ing", "");
    }
    
    return str;
}

// Step 1c of the Porter stemming algorithm: Handle "y" to "i" conversion
std::string Stemmer::step1c(const std::string& str) {
    if (ends_with(str, "y") && containsVowel(str.substr(0, str.length() - 1))) {
        return replaceEnding(str, "y", "i");
    }
    return str;
}

// Step 2 of the Porter stemming algorithm: Handle more complex suffixes
std::string Stemmer::step2(const std::string& str) {
    if (ends_with(str, "ational")) return replaceEnding(str, "ational", "ate");
    if (ends_with(str, "tional")) return replaceEnding(str, "tional", "tion");
    if (ends_with(str, "enci")) return replaceEnding(str, "enci", "ence");
    if (ends_with(str, "anci")) return replaceEnding(str, "anci", "ance");
    return str;
}

// Step 3 of the Porter stemming algorithm: Handle additional suffixes
std::string Stemmer::step3(const std::string& str) {
    if (ends_with(str, "icate")) return replaceEnding(str, "icate", "ic");
    if (ends_with(str, "ative")) return replaceEnding(str, "ative", "");
    if (ends_with(str, "alize")) return replaceEnding(str, "alize", "al");
    return str;
}

// Step 4 of the Porter stemming algorithm: Handle common suffix removal
std::string Stemmer::step4(const std::string& str) {
    if (ends_with(str, "ment")) return replaceEnding(str, "ment", "");
    if (ends_with(str, "ness")) return replaceEnding(str, "ness", "");
    if (ends_with(str, "tion")) return replaceEnding(str, "tion", "t");
    return str;
}

// Step 5 of the Porter stemming algorithm: Final cleanup
std::string Stemmer::step5(const std::string& str) {
    if (ends_with(str, "e") && str.length() > 4) {
        return replaceEnding(str, "e", "");
    }
    return str;
}
