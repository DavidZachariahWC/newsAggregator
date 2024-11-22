#include "QueryProcessor.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Stemmer.h"

// Constructor initializes the QueryProcessor with an IndexHandler reference
QueryProcessor::QueryProcessor(IndexHandler* indexHandler) 
    : indexHandler(indexHandler) {}

// Processes a query string, retrieves results, and displays them
std::vector<std::shared_ptr<Document>> QueryProcessor::processQuery(const std::string& queryString) {
    clearQueryComponents(); // Reset query components from previous queries
    parseQuery(queryString); // Parse the query string into components

    // Retrieve relevant documents based on parsed query
    auto results = indexHandler->getRelevantDocuments(terms, excludedTerms, organizations, persons);

    displayResults(results); // Display the search results
    return results;
}

// Parses a query string into terms, excluded terms, organizations, and persons
void QueryProcessor::parseQuery(const std::string& queryString) {
    std::istringstream iss(queryString);
    std::string token;
    std::string currentOrg, currentPerson;
    bool readingOrg = false, readingPerson = false;

    // Tokenize the query string and categorize tokens
    while (iss >> token) {
        if (token.substr(0, 4) == "ORG:") {
            readingOrg = true;
            readingPerson = false;
            currentOrg = token.substr(4); // Start reading an organization
        } else if (token.substr(0, 7) == "PERSON:") {
            readingPerson = true;
            readingOrg = false;
            currentPerson = token.substr(7); // Start reading a person
        } else if (token[0] == '-') {
            readingOrg = false;
            readingPerson = false;
            excludedTerms.push_back(stemmer.stemWord(token.substr(1))); // Add excluded term
        } else if (readingOrg) {
            currentOrg += " " + token; // Append to current organization
        } else if (readingPerson) {
            currentPerson += " " + token; // Append to current person
        } else {
            terms.push_back(stemmer.stemWord(token)); // Add to terms
        }
    }

    // Finalize any partially-read organizations or persons
    if (readingOrg && !currentOrg.empty()) {
        organizations.push_back(currentOrg);
    }
    if (readingPerson && !currentPerson.empty()) {
        persons.push_back(currentPerson);
    }
}

// Displays search results and allows user to view full documents
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

    // Allow user to view a full document
    std::cout << "\nEnter a number to view the full document (0 to continue): ";
    int choice;
    
    // Handle invalid input
    if (!(std::cin >> choice)) {
        std::cin.clear(); // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear trailing input

    // Validate selection
    if (choice > 0 && choice <= count) {
        displayDocument(results[choice - 1]); // Display the selected document
    } else if (choice != 0) {
        std::cout << "Invalid selection.\n";
    }
}

// Displays the full content of a selected document
void QueryProcessor::displayDocument(const std::shared_ptr<Document>& doc) {
    if (!doc) return; // Safety check for null documents

    std::cout << "\n========================================\n";
    std::cout << "Title: " << doc->getTitle() << "\n";
    std::cout << "Publication: " << doc->getPublication() << "\n";
    std::cout << "Date: " << doc->getDatePublished() << "\n";

    // Display metadata
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

    // Display the full text
    std::cout << "\nText:\n";
    std::cout << doc->getText() << "\n";
    std::cout << "========================================\n";

    // Wait for user input before continuing
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

// Clears stored query components (terms, exclusions, organizations, persons)
void QueryProcessor::clearQueryComponents() {
    terms.clear();
    excludedTerms.clear();
    organizations.clear();
    persons.clear();
}
