#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "IndexHandler.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"
#include <memory>

// The UserInterface class provides an interactive interface for the user
// to interact with the document indexing and query system.
class UserInterface {
public:
    // Constructor initializes the UserInterface by setting up components
    UserInterface();

    // Starts the main loop for the user interface
    void start();

private:
    // Unique pointers to core components of the system
    std::unique_ptr<IndexHandler> indexHandler; // Manages document indices
    std::unique_ptr<DocumentParser> docParser; // Parses documents and directories
    std::unique_ptr<QueryProcessor> queryProcessor; // Processes search queries

    // Displays the main menu options to the user
    void displayMenu();

    // Handles the user's menu choice and executes the corresponding action
    void handleUserInput();
    
    // Prompts the user for a directory path and creates a new index
    void createIndex();

    // Prompts the user for a file path and saves the current index
    void saveIndex();

    // Prompts the user for a file path and loads an existing index
    void loadIndex();

    // Allows the user to enter a search query and processes it
    void enterQuery();
};

#endif
