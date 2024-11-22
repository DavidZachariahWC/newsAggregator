#include "UserInterface.h"
#include <iostream>
#include <limits>

// Constructor initializes the UserInterface by creating instances of core components
UserInterface::UserInterface() {
    indexHandler = std::make_unique<IndexHandler>(); // Handles document indexing
    docParser = std::make_unique<DocumentParser>(); // Parses documents from a directory
    queryProcessor = std::make_unique<QueryProcessor>(indexHandler.get()); // Processes queries using the index
}

// Starts the main program loop, repeatedly displaying the menu and handling user input
void UserInterface::start() {
    while (true) {
        displayMenu(); // Show the main menu
        handleUserInput(); // Process user input
    }
}

// Displays the main menu options to the user
void UserInterface::displayMenu() {
    std::cout << "\n======================\n";
    std::cout << "SuperSearch Menu\n"; // Program name
    std::cout << "======================\n";
    std::cout << "i - Create new index\n"; // Option to create a new index
    std::cout << "s - Save index to file\n"; // Option to save the current index
    std::cout << "l - Load index from file\n"; // Option to load an existing index
    std::cout << "q - Enter query\n"; // Option to perform a search query
    std::cout << "e - Exit\n"; // Option to exit the program
    std::cout << "======================\n";
    std::cout << "Enter choice: ";
}

// Handles user input based on the menu options
void UserInterface::handleUserInput() {
    char choice;
    std::cin >> choice; // Read the user's choice
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    switch (choice) {
        case 'i': // Create a new index
        case 'I':
            createIndex();
            break;
        case 's': // Save the index to a file
        case 'S':
            saveIndex();
            break;
        case 'l': // Load an index from a file
        case 'L':
            loadIndex();
            break;
        case 'q': // Enter a search query
        case 'Q':
            enterQuery();
            break;
        case 'e': // Exit the program
        case 'E':
            std::cout << "Exiting program\n";
            exit(0);
        default: // Handle invalid choices
            std::cout << "Invalid choice. Please try again.\n";
    }
}

// Prompts the user to provide a directory path and creates a new index
void UserInterface::createIndex() {
    std::cout << "Enter directory path to index: ";
    std::string directoryPath;
    std::getline(std::cin, directoryPath); // Get the directory path from the user

    std::cout << "Indexing documents from " << directoryPath << "...\n";
    
    try {
        // Parse all documents in the specified directory
        auto documents = docParser->parseDirectory(directoryPath);
        
        std::cout << "Found " << documents.size() << " documents.\n";
        std::cout << "Adding documents to index...\n";
        
        // Add each document to the index
        for (const auto& doc : documents) {
            indexHandler->addDocument(doc);
        }
        
        std::cout << "Indexing complete.\n";
    }
    catch (const std::exception& e) { // Handle any errors during indexing
        std::cerr << "Error during indexing: " << e.what() << std::endl;
    }
}

// Prompts the user to save the index to a specified file path
void UserInterface::saveIndex() {
    std::cout << "Enter file path to save index: ";
    std::string filePath;
    std::getline(std::cin, filePath); // Get the file path from the user

    try {
        indexHandler->saveIndices(filePath); // Save the index to the file
        std::cout << "Index saved successfully.\n";
    }
    catch (const std::exception& e) { // Handle errors during saving
        std::cerr << "Error saving index: " << e.what() << std::endl;
    }
}

// Prompts the user to load an index from a specified file path
void UserInterface::loadIndex() {
    std::cout << "Enter file path to load index: ";
    std::string filePath;
    std::getline(std::cin, filePath); // Get the file path from the user

    try {
        indexHandler->loadIndices(filePath); // Load the index from the file
        std::cout << "Index loaded successfully.\n";
    }
    catch (const std::exception& e) { // Handle errors during loading
        std::cerr << "Error loading index: " << e.what() << std::endl;
    }
}

// Prompts the user to enter a search query and processes it
void UserInterface::enterQuery() {
    std::cout << "\nEnter your search query:\n";
    std::cout << "  - Use -term to exclude terms\n"; // Provide usage instructions
    std::cout << "Query: ";
    
    std::string queryString;
    std::getline(std::cin, queryString); // Get the query from the user

    try {
        queryProcessor->processQuery(queryString); // Process the query using the query processor
    }
    catch (const std::exception& e) { // Handle errors during query processing
        std::cerr << "Error processing query: " << e.what() << std::endl;
    }
}
