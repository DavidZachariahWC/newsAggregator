#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "IndexHandler.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"
#include <memory>

class UserInterface {
public:
    UserInterface();
    void start();

private:
    std::unique_ptr<IndexHandler> indexHandler;
    std::unique_ptr<DocumentParser> docParser;
    std::unique_ptr<QueryProcessor> queryProcessor;

    void displayMenu();
    void handleUserInput();
    
    void createIndex();
    void saveIndex();
    void loadIndex();
    void enterQuery();
};

#endif 