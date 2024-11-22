#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "IndexHandler.h" // Handles the inverted index
#include "DocumentParser.h" // Parses documents for indexing
#include "QueryProcessor.h" // Processes user queries
#include <memory> // Smart pointers for memory management

/**
 * @class UserInterface
 * @brief Text-based interface for the search engine.
 *
 * Manages user input and integrates functionality such as indexing, saving/loading,
 * and querying financial news articles.
 */
class UserInterface {
public:
    /**
     * @brief Initializes the search engine components.
     */
    UserInterface();

    /**
     * @brief Starts the menu-driven user interface.
     */
    void start();

private:
    std::unique_ptr<IndexHandler> indexHandler; // Manages the inverted index
    std::unique_ptr<DocumentParser> docParser; // Parses documents
    std::unique_ptr<QueryProcessor> queryProcessor; // Handles queries

    /**
     * @brief Displays the main menu options.
     */
    void displayMenu();

    /**
     * @brief Handles user input and executes corresponding actions.
     */
    void handleUserInput();

    /**
     * @brief Builds the index from a directory of documents.
     */
    void createIndex();

    /**
     * @brief Saves the index to a file for persistence.
     */
    void saveIndex();

    /**
     * @brief Loads a previously saved index from a file.
     */
    void loadIndex();

    /**
     * @brief Allows the user to input and execute search queries.
     */
    void enterQuery();
};

#endif
