#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <unordered_map>

class Document {
public:
    Document();
    Document(const std::string& filePath);

    // Getters
    std::string getTitle() const { return title; }
    std::string getPublication() const { return publication; }
    std::string getDatePublished() const { return datePublished; }
    std::string getText() const;
    std::string getProcessedText() const;
    std::vector<std::string> getAuthors() const { return authors; }
    std::vector<std::string> getOrganizations() const { return organizations; }
    std::vector<std::string> getPersons() const { return persons; }
    std::string getFilePath() const { return filePath; }
    
    // Term frequency getter
    int getTermFrequency(const std::string& term) const;
    
    // Setters
    void setTitle(const std::string& title) { this->title = title; }
    void setPublication(const std::string& publication) { this->publication = publication; }
    void setDatePublished(const std::string& date) { this->datePublished = date; }
    void setText(const std::string& text);
    void setAuthors(const std::vector<std::string>& authors) { this->authors = authors; }
    void setOrganizations(const std::vector<std::string>& orgs) { this->organizations = orgs; }
    void setPersons(const std::vector<std::string>& persons) { this->persons = persons; }
    void setFilePath(const std::string& filePath) { this->filePath = filePath; }
    void setProcessedText(const std::string& processedText);

private:
    std::string title;
    std::string publication;
    std::string datePublished;
    std::string text;
    std::string originalText;
    std::vector<std::string> authors;
    std::vector<std::string> organizations;
    std::vector<std::string> persons;
    std::string filePath;
    
    // Store term frequencies for ranking
    std::unordered_map<std::string, int> termFrequencies;
};

#endif 