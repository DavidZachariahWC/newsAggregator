#include <iostream>
#include <string>
#include "IndexHandler.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"
#include "UserInterface.h"

void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  supersearch index <directory>\n";
    std::cout << "  supersearch query \"<query>\"\n";
    std::cout << "  supersearch ui\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];

    try {
        if (command == "index") {
            if (argc < 3) {
                std::cout << "Please specify a directory to index.\n";
                return 1;
            }
            std::string directoryPath = argv[2];

            // Create objects
            auto indexHandler = std::make_unique<IndexHandler>();
            auto docParser = std::make_unique<DocumentParser>();

            // Parse and index documents
            std::cout << "Indexing documents...\n";
            auto documents = docParser->parseDirectory(directoryPath);
            
            for (const auto& doc : documents) {
                indexHandler->addDocument(doc);
            }

            // Save indices
            indexHandler->saveIndices("index.dat");
            std::cout << "Indexing complete. Index saved to 'index.dat'\n";

        } else if (command == "query") {
            if (argc < 3) {
                std::cout << "Please specify a query.\n";
                return 1;
            }
            std::string queryString = argv[2];

            // Create objects and load index
            auto indexHandler = std::make_unique<IndexHandler>();
            indexHandler->loadIndices("index.dat");
            
            auto queryProcessor = std::make_unique<QueryProcessor>(indexHandler.get());
            queryProcessor->processQuery(queryString);

        } else if (command == "ui") {
            UserInterface ui;
            ui.start();
        } else {
            std::cout << "Unknown command: " << command << std::endl;
            printUsage();
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} 