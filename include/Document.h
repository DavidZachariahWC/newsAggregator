#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <unordered_map>

// Document class representing a news article with metadata and content
class Document {
public:
    Document(); // Default constructor
    Document(const std::string& filePath); // Constructor to initialize a document from a file

    // Getters for retrieving metadata and content
    std::string getTitle() const { return title; } // Get the document title
    std::string getPublication() const { return publication; } // Get the publication name
    std::string getDatePublished() const { return datePublished; } // Get the publication date
    std::string getText() const; // Get the article's original text
    std::string getProcessedText() const; // Get the processed text for indexing
    std::vector<std::string> getAuthors() const { return authors; } // Get a list of authors
    std::vector<std::string> getOrganizations() const { return organizations; } // Get associated organizations
    std::vector<std::string> getPersons() const { return persons; } // Get associated persons
    std::string getFilePath() const { return filePath; } // Get the file path

    // Retrieve the frequency of a specific term in the document
    int getTermFrequency(const std::string& term) const;

    // Setters for updating metadata and content
    void setTitle(const std::string& title) { this->title = title; }
    void setPublication(const std::string& publication) { this->publication = publication; }
    void setDatePublished(const std::string& date) { this->datePublished = date; }
    void setText(const std::string& text); // Set the original article text
    void setAuthors(const std::vector<std::string>& authors) { this->authors = authors; }
    void setOrganizations(const std::vector<std::string>& orgs) { this->organizations = orgs; }
    void setPersons(const std::vector<std::string>& persons) { this->persons = persons; }
    void setFilePath(const std::string& filePath) { this->filePath = filePath; }
    void setProcessedText(const std::string& processedText); // Set the processed text for indexing

private:
    // Metadata fields for the document
    std::string title; // Title of the article
    std::string publication; // Name of the publication
    std::string datePublished; // Publication date
    std::string text; // Full text of the article
    std::string originalText; // Unprocessed original text
    std::vector<std::string> authors; // List of authors
    std::vector<std::string> organizations; // List of associated organizations
    std::vector<std::string> persons; // List of associated persons
    std::string filePath; // File path for the document

    // Map to store term frequencies for relevancy ranking
    std::unordered_map<std::string, int> termFrequencies;
};

#endif
