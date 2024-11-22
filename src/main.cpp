#include <iostream>
#include <string>
#include "IndexHandler.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"
#include "UserInterface.h"

// Prints usage instructions for the program
void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  supersearch index <directory>\n"; // Command to index a directory
    std::cout << "  supersearch query \"<query>\"\n"; // Command to execute a search query
    std::cout << "  supersearch ui\n";               // Command to start the interactive UI
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        // If no arguments are provided, display usage instructions
        printUsage();
        return 1; // Exit with an error code
    }

    std::string command = argv[1]; // Get the command from the command-line arguments

    try {
        if (command == "index") {
            // Handle the "index" command
            if (argc < 3) {
                // Ensure a directory path is provided
                std::cout << "Please specify a directory to index.\n";
                return 1;
            }
            std::string directoryPath = argv[2]; // Directory to index

            // Create objects for indexing
            auto indexHandler = std::make_unique<IndexHandler>();
            auto docParser = std::make_unique<DocumentParser>();

            // Parse documents from the directory and add them to the index
            std::cout << "Indexing documents...\n";
            auto documents = docParser->parseDirectory(directoryPath);
            
            for (const auto& doc : documents) {
                indexHandler->addDocument(doc); // Add each document to the index
            }

            // Save the index to a file
            indexHandler->saveIndices("index.dat");
            std::cout << "Indexing complete. Index saved to 'index.dat'\n";

        } else if (command == "query") {
            // Handle the "query" command
            if (argc < 3) {
                // Ensure a query string is provided
                std::cout << "Please specify a query.\n";
                return 1;
            }
            std::string queryString = argv[2]; // Query string from the command line

            // Create objects and load the index
            auto indexHandler = std::make_unique<IndexHandler>();
            indexHandler->loadIndices("index.dat"); // Load the previously saved index
            
            auto queryProcessor = std::make_unique<QueryProcessor>(indexHandler.get());
            queryProcessor->processQuery(queryString); // Process the query

        } else if (command == "ui") {
            // Handle the "ui" command to start the interactive User Interface
            UserInterface ui;
            ui.start(); // Start the UI loop
        } else {
            // Handle unknown commands
            std::cout << "Unknown command: " << command << std::endl;
            printUsage(); // Display usage instructions for valid commands
            return 1; // Exit with an error code
        }
    }
    catch (const std::exception& e) {
        // Catch and display any exceptions that occur during program execution
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Exit with an error code
    }

    return 0; // Exit successfully
}
