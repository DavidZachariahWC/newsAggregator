#include "Stemmer.h"
#include <algorithm>
#include <string>

// Helper function to check if a string ends with a specific suffix
bool ends_with(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

// Applies the Porter stemming algorithm to reduce a word to its root form
std::string Stemmer::stemWord(const std::string& word) {
    if (word.length() <= 2) return word; // Skip very short words

    // Convert the word to lowercase for consistency
    std::string str = word;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    // Apply Porter stemming steps sequentially
    str = step1a(str);
    str = step1b(str);
    str = step1c(str);
    str = step2(str);
    str = step3(str);
    str = step4(str);
    str = step5(str);

    return str; // Return the stemmed word
}

// Checks if the character at a specific position is a consonant
bool Stemmer::isConsonant(const std::string& str, int i) {
    char c = str[i];
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return false;
    if (c == 'y') {
        return (i == 0) ? true : !isConsonant(str, i - 1);
    }
    return true;
}

// Counts the number of consonant-vowel sequences (measures) in the word
int Stemmer::countConsonantSequences(const std::string& str) {
    int count = 0;
    bool inConsonant = false;

    for (size_t i = 0; i < str.length(); i++) {
        if (isConsonant(str, i)) {
            if (!inConsonant) {
                count++;
                inConsonant = true;
            }
        } else {
            inConsonant = false;
        }
    }
    return count;
}

// Checks if the word contains at least one vowel
bool Stemmer::containsVowel(const std::string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!isConsonant(str, i)) return true;
    }
    return false;
}

// Checks if the word ends with a double consonant
bool Stemmer::endsWithDoubleConsonant(const std::string& str) {
    if (str.length() < 2) return false;
    return (isConsonant(str, str.length() - 1) && 
            isConsonant(str, str.length() - 2) &&
            str[str.length() - 1] == str[str.length() - 2]);
}

// Checks if the word ends with a consonant-vowel-consonant (CVC) sequence
bool Stemmer::endsWithCVC(const std::string& str) {
    if (str.length() < 3) return false;

    size_t last = str.length() - 1;
    char last_char = str[last];

    return (isConsonant(str, last - 2) &&
            !isConsonant(str, last - 1) &&
            isConsonant(str, last) &&
            last_char != 'w' && last_char != 'x' && last_char != 'y');
}

// Replaces a specific suffix of the word with another suffix
std::string Stemmer::replaceEnding(const std::string& str, 
                                   const std::string& oldEnd, 
                                   const std::string& newEnd) {
    if (str.length() < oldEnd.length()) return str;

    std::string ending = str.substr(str.length() - oldEnd.length());
    if (ending == oldEnd) {
        return str.substr(0, str.length() - oldEnd.length()) + newEnd;
    }
    return str;
}

// Implementation of Porter algorithm steps
// Step 1a: Handles plurals and simple suffixes
std::string Stemmer::step1a(const std::string& str) {
    if (ends_with(str, "sses")) return replaceEnding(str, "sses", "ss");
    if (ends_with(str, "ies")) return replaceEnding(str, "ies", "i");
    if (ends_with(str, "ss")) return str;
    if (ends_with(str, "s")) return replaceEnding(str, "s", "");
    return str;
}

// Step 1b: Handles past tense and -ing suffixes
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

// Step 1c: Replaces terminal 'y' with 'i' if preceded by a vowel
std::string Stemmer::step1c(const std::string& str) {
    if (ends_with(str, "y") && containsVowel(str.substr(0, str.length() - 1))) {
        return replaceEnding(str, "y", "i");
    }
    return str;
}

// Step 2: Handles various suffixes
std::string Stemmer::step2(const std::string& str) {
    if (ends_with(str, "ational")) return replaceEnding(str, "ational", "ate");
    if (ends_with(str, "tional")) return replaceEnding(str, "tional", "tion");
    if (ends_with(str, "enci")) return replaceEnding(str, "enci", "ence");
    if (ends_with(str, "anci")) return replaceEnding(str, "anci", "ance");
    return str;
}

// Step 3: Simplifies additional suffixes
std::string Stemmer::step3(const std::string& str) {
    if (ends_with(str, "icate")) return replaceEnding(str, "icate", "ic");
    if (ends_with(str, "ative")) return replaceEnding(str, "ative", "");
    if (ends_with(str, "alize")) return replaceEnding(str, "alize", "al");
    return str;
}

// Step 4: Removes common suffixes
std::string Stemmer::step4(const std::string& str) {
    if (ends_with(str, "ment")) return replaceEnding(str, "ment", "");
    if (ends_with(str, "ness")) return replaceEnding(str, "ness", "");
    if (ends_with(str, "tion")) return replaceEnding(str, "tion", "t");
    return str;
}

// Step 5: Handles terminal 'e'
std::string Stemmer::step5(const std::string& str) {
    if (ends_with(str, "e") && str.length() > 4) {
        return replaceEnding(str, "e", "");
    }
    return str;
}
