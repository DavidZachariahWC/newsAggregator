#include <iostream>
#include <string>
#include "IndexHandler.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"
#include "UserInterface.h"

// Prints usage instructions for the command-line interface
void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  supersearch index <directory>\n";
    std::cout << "  supersearch query \"<query>\"\n";
    std::cout << "  supersearch ui\n";
}

// Entry point of the application
int main(int argc, char* argv[]) {
    if (argc < 2) {  // Check if at least one command is provided
        printUsage();
        return 1;
    }

    std::string command = argv[1]; // Extract the command

    try {
        if (command == "index") {
            // Command to index a directory
            if (argc < 3) {  // Ensure the directory path is specified
                std::cout << "Please specify a directory to index.\n";
                return 1;
            }
            std::string directoryPath = argv[2];

            // Create instances of IndexHandler and DocumentParser
            auto indexHandler = std::make_unique<IndexHandler>();
            auto docParser = std::make_unique<DocumentParser>();

            // Parse documents from the directory
            std::cout << "Indexing documents...\n";
            auto documents = docParser->parseDirectory(directoryPath);

            // Add documents to the index
            for (const auto& doc : documents) {
                indexHandler->addDocument(doc);
            }

            // Save the index to a file
            indexHandler->saveIndices("index.dat");
            std::cout << "Indexing complete. Index saved to 'index.dat'\n";

        } else if (command == "query") {
            // Command to process a search query
            if (argc < 3) {  // Ensure the query is provided
                std::cout << "Please specify a query.\n";
                return 1;
            }
            std::string queryString = argv[2];

            // Load the index and process the query
            auto indexHandler = std::make_unique<IndexHandler>();
            indexHandler->loadIndices("index.dat"); // Load saved index

            auto queryProcessor = std::make_unique<QueryProcessor>(indexHandler.get());
            queryProcessor->processQuery(queryString); // Execute the query

        } else if (command == "ui") {
            // Command to start the interactive user interface
            UserInterface ui;
            ui.start();

        } else {
            // Handle unknown commands
            std::cout << "Unknown command: " << command << std::endl;
            printUsage();
            return 1;
        }
    } catch (const std::exception& e) {
        // Catch and display errors
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0; // Exit successfully
}
