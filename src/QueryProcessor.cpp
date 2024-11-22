#include "QueryProcessor.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Stemmer.h"

// Constructor that initializes the QueryProcessor with a reference to an IndexHandler
QueryProcessor::QueryProcessor(IndexHandler* indexHandler) 
    : indexHandler(indexHandler) {}

// Processes a query string and returns the matching documents
std::vector<std::shared_ptr<Document>> QueryProcessor::processQuery(const std::string& queryString) {
    // Clear any previously stored query components
    clearQueryComponents();

    // Parse the query string to extract terms, exclusions, organizations, and persons
    parseQuery(queryString);

    // Retrieve relevant documents based on the parsed query components
    auto results = indexHandler->getRelevantDocuments(terms, excludedTerms, organizations, persons);

    // Display the results to the user
    displayResults(results);

    return results; // Return the list of matching documents
}

// Parses the query string into different components (terms, exclusions, organizations, persons)
void QueryProcessor::parseQuery(const std::string& queryString) {
    std::istringstream iss(queryString); // Stream to process the query string
    std::string token;
    std::string currentOrg;    // Accumulates organization names
    std::string currentPerson; // Accumulates person names
    bool readingOrg = false;   // Indicates if the current token is part of an organization
    bool readingPerson = false;// Indicates if the current token is part of a person name

    while (iss >> token) {
        if (token.substr(0, 4) == "ORG:") { // Check if the token starts with "ORG:"
            readingOrg = true;
            readingPerson = false;
            currentOrg = token.substr(4); // Extract the organization name
        }
        else if (token.substr(0, 7) == "PERSON:") { // Check if the token starts with "PERSON:"
            readingPerson = true;
            readingOrg = false;
            currentPerson = token.substr(7); // Extract the person's name
        }
        else if (token[0] == '-') { // Check if the token starts with a '-' (excluded term)
            readingOrg = false;
            readingPerson = false;
            excludedTerms.push_back(stemmer.stemWord(token.substr(1))); // Add to excluded terms after stemming
        }
        else if (readingOrg) { // Continue reading an organization name
            currentOrg += " " + token;
        }
        else if (readingPerson) { // Continue reading a person's name
            currentPerson += " " + token;
        }
        else { // Treat the token as a term
            terms.push_back(stemmer.stemWord(token)); // Add to terms after stemming
        }
    }

    // Add the accumulated organization to the list if applicable
    if (readingOrg && !currentOrg.empty()) {
        organizations.push_back(currentOrg);
    }
    // Add the accumulated person to the list if applicable
    if (readingPerson && !currentPerson.empty()) {
        persons.push_back(currentPerson);
    }
}

// Displays the query results to the user
void QueryProcessor::displayResults(const std::vector<std::shared_ptr<Document>>& results) {
    if (results.empty()) { // If no results found
        std::cout << "No results found.\n";
        return;
    }

    // Display the number of results found
    std::cout << "\nFound " << results.size() << " results:\n";
    std::cout << "----------------------------------------\n";

    // Display up to 15 results with details
    int count = 0;
    for (const auto& doc : results) {
        if (count >= 15) break; // Limit the output to 15 results

        std::cout << count + 1 << ". " << doc->getTitle() << "\n";
        std::cout << "   Publication: " << doc->getPublication() << "\n";
        std::cout << "   Date: " << doc->getDatePublished() << "\n";
        std::cout << "----------------------------------------\n";
        count++;
    }

    // Prompt the user to view the full document or continue
    std::cout << "\nEnter a number to view the full document (0 to continue): ";
    int choice;

    // Handle invalid user input
    if (!(std::cin >> choice)) {
        std::cin.clear(); // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        return;
    }

    // Clear any remaining characters in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Display the selected document if the choice is valid
    if (choice > 0 && choice <= count) {
        displayDocument(results[choice - 1]); // Show the selected document
    } else if (choice != 0) {
        std::cout << "Invalid selection.\n"; // Handle invalid selection
    }
}

// Displays the full details of a selected document
void QueryProcessor::displayDocument(const std::shared_ptr<Document>& doc) {
    if (!doc) return; // Return if the document is null

    // Display detailed document information
    std::cout << "\n========================================\n";
    std::cout << "Title: " << doc->getTitle() << "\n";
    std::cout << "Publication: " << doc->getPublication() << "\n";
    std::cout << "Date: " << doc->getDatePublished() << "\n";
    
    // Display authors
    std::cout << "\nAuthors: ";
    for (const auto& author : doc->getAuthors()) {
        std::cout << author << ", ";
    }
    std::cout << "\n";

    // Display organizations mentioned
    std::cout << "\nOrganizations mentioned: ";
    for (const auto& org : doc->getOrganizations()) {
        std::cout << org << ", ";
    }
    std::cout << "\n";

    // Display persons mentioned
    std::cout << "\nPersons mentioned: ";
    for (const auto& person : doc->getPersons()) {
        std::cout << person << ", ";
    }
    std::cout << "\n";

    // Display the document's full text
    std::cout << "\nText:\n";
    std::cout << doc->getText() << "\n"; // Display the original text
    std::cout << "========================================\n";

    // Wait for user to press Enter before continuing
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

// Clears all query components before processing a new query
void QueryProcessor::clearQueryComponents() {
    terms.clear();        // Clear the list of terms
    excludedTerms.clear();// Clear the list of excluded terms
    organizations.clear();// Clear the list of organizations
    persons.clear();      // Clear the list of persons
}
