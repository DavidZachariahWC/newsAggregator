#include "UserInterface.h"
#include <iostream>
#include <limits>

UserInterface::UserInterface() {
    indexHandler = std::make_unique<IndexHandler>();
    docParser = std::make_unique<DocumentParser>();
    queryProcessor = std::make_unique<QueryProcessor>(indexHandler.get());
}

void UserInterface::start() {
    while (true) {
        displayMenu();
        handleUserInput();
    }
}

void UserInterface::displayMenu() {
    std::cout << "\n======================\n";
    std::cout << "SuperSearch Menu\n";
    std::cout << "======================\n";
    std::cout << "i - Create new index\n";
    std::cout << "s - Save index to file\n";
    std::cout << "l - Load index from file\n";
    std::cout << "q - Enter query\n";
    std::cout << "e - Exit\n";
    std::cout << "======================\n";
    std::cout << "Enter choice: ";
}

void UserInterface::handleUserInput() {
    char choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 'i':
        case 'I':
            createIndex();
            break;
        case 's':
        case 'S':
            saveIndex();
            break;
        case 'l':
        case 'L':
            loadIndex();
            break;
        case 'q':
        case 'Q':
            enterQuery();
            break;
        case 'e':
        case 'E':
            std::cout << "Exiting program\n";
            exit(0);
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

void UserInterface::createIndex() {
    std::cout << "Enter directory path to index: ";
    std::string directoryPath;
    std::getline(std::cin, directoryPath);

    std::cout << "Indexing documents from " << directoryPath << "...\n";
    
    try {
        auto documents = docParser->parseDirectory(directoryPath);
        
        std::cout << "Found " << documents.size() << " documents.\n";
        std::cout << "Adding documents to index...\n";
        
        for (const auto& doc : documents) {
            indexHandler->addDocument(doc);
        }
        
        std::cout << "Indexing complete.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error during indexing: " << e.what() << std::endl;
    }
}

void UserInterface::saveIndex() {
    std::cout << "Enter file path to save index: ";
    std::string filePath;
    std::getline(std::cin, filePath);

    try {
        indexHandler->saveIndices(filePath);
        std::cout << "Index saved successfully.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving index: " << e.what() << std::endl;
    }
}

void UserInterface::loadIndex() {
    std::cout << "Enter file path to load index: ";
    std::string filePath;
    std::getline(std::cin, filePath);

    try {
        indexHandler->loadIndices(filePath);
        std::cout << "Index loaded successfully.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading index: " << e.what() << std::endl;
    }
}

void UserInterface::enterQuery() {
    std::cout << "\nEnter your search query:\n";
    std::cout << "  - Use -term to exclude terms\n";
    std::cout << "Query: ";
    
    std::string queryString;
    std::getline(std::cin, queryString);

    try {
        queryProcessor->processQuery(queryString);
    }
    catch (const std::exception& e) {
        std::cerr << "Error processing query: " << e.what() << std::endl;
    }
} 