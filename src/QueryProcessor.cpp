#include "QueryProcessor.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Stemmer.h"

QueryProcessor::QueryProcessor(IndexHandler* indexHandler) 
    : indexHandler(indexHandler) {}

std::vector<std::shared_ptr<Document>> QueryProcessor::processQuery(const std::string& queryString) {
    // Clear previous query components
    clearQueryComponents();

    // Parse the query
    parseQuery(queryString);

    // Get and return results
    auto results = indexHandler->getRelevantDocuments(terms, excludedTerms, organizations, persons);

    // Display results
    displayResults(results);

    return results;
}

void QueryProcessor::parseQuery(const std::string& queryString) {
    std::istringstream iss(queryString);
    std::string token;
    std::string currentOrg;
    std::string currentPerson;
    bool readingOrg = false;
    bool readingPerson = false;

    while (iss >> token) {
        if (token.substr(0, 4) == "ORG:") {
            readingOrg = true;
            readingPerson = false;
            currentOrg = token.substr(4);
        }
        else if (token.substr(0, 7) == "PERSON:") {
            readingPerson = true;
            readingOrg = false;
            currentPerson = token.substr(7);
        }
        else if (token[0] == '-') {
            readingOrg = false;
            readingPerson = false;
            excludedTerms.push_back(stemmer.stemWord(token.substr(1)));
        }
        else if (readingOrg) {
            currentOrg += " " + token;
        }
        else if (readingPerson) {
            currentPerson += " " + token;
        }
        else {
            terms.push_back(stemmer.stemWord(token));
        }
    }

    if (readingOrg && !currentOrg.empty()) {
        organizations.push_back(currentOrg);
    }
    if (readingPerson && !currentPerson.empty()) {
        persons.push_back(currentPerson);
    }
}

void QueryProcessor::displayResults(const std::vector<std::shared_ptr<Document>>& results) {
    if (results.empty()) {
        std::cout << "No results found.\n";
        return;
    }

    std::cout << "\nFound " << results.size() << " results:\n";
    std::cout << "----------------------------------------\n";

    // Display up to 15 results
    int count = 0;
    for (const auto& doc : results) {
        if (count >= 15) break;

        std::cout << count + 1 << ". " << doc->getTitle() << "\n";
        std::cout << "   Publication: " << doc->getPublication() << "\n";
        std::cout << "   Date: " << doc->getDatePublished() << "\n";
        std::cout << "----------------------------------------\n";
        count++;
    }

    // Prompt user to view full document
    std::cout << "\nEnter a number to view the full document (0 to continue): ";
    int choice;
    
    // Handle invalid input
    if (!(std::cin >> choice)) {
        std::cin.clear();  // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
        return;
    }

    // Clear any remaining characters in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Validate choice range
    if (choice > 0 && choice <= count) {
        displayDocument(results[choice - 1]);
    } else if (choice != 0) {
        std::cout << "Invalid selection.\n";
    }
}

void QueryProcessor::displayDocument(const std::shared_ptr<Document>& doc) {
    if (!doc) return;  // Safety check

    std::cout << "\n========================================\n";
    std::cout << "Title: " << doc->getTitle() << "\n";
    std::cout << "Publication: " << doc->getPublication() << "\n";
    std::cout << "Date: " << doc->getDatePublished() << "\n";
    
    std::cout << "\nAuthors: ";
    for (const auto& author : doc->getAuthors()) {
        std::cout << author << ", ";
    }
    std::cout << "\n";

    std::cout << "\nOrganizations mentioned: ";
    for (const auto& org : doc->getOrganizations()) {
        std::cout << org << ", ";
    }
    std::cout << "\n";

    std::cout << "\nPersons mentioned: ";
    for (const auto& person : doc->getPersons()) {
        std::cout << person << ", ";
    }
    std::cout << "\n";

    std::cout << "\nText:\n";
    std::cout << doc->getText() << "\n";  // This will show the original text
    std::cout << "========================================\n";

    // Wait for user input before continuing
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void QueryProcessor::clearQueryComponents() {
    terms.clear();
    excludedTerms.clear();
    organizations.clear();
    persons.clear();
} 