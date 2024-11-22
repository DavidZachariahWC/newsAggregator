#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <unordered_map>

// The Document class represents a document with various metadata and textual content.
// It provides methods to set and get attributes, as well as calculate term frequencies.
class Document {
public:
    // Constructors
    Document(); // Default constructor
    Document(const std::string& filePath); // Constructor with file path

    // Getters for metadata fields
    std::string getTitle() const { return title; } // Get the title of the document
    std::string getPublication() const { return publication; } // Get the publication name
    std::string getDatePublished() const { return datePublished; } // Get the date published
    std::string getText() const; // Get the original text of the document
    std::string getProcessedText() const; // Get the processed text of the document
    std::vector<std::string> getAuthors() const { return authors; } // Get the list of authors
    std::vector<std::string> getOrganizations() const { return organizations; } // Get the list of organizations
    std::vector<std::string> getPersons() const { return persons; } // Get the list of persons
    std::string getFilePath() const { return filePath; } // Get the file path of the document
    
    // Retrieves the frequency of a specific term in the document
    int getTermFrequency(const std::string& term) const;

    // Setters for metadata fields
    void setTitle(const std::string& title) { this->title = title; } // Set the title of the document
    void setPublication(const std::string& publication) { this->publication = publication; } // Set the publication name
    void setDatePublished(const std::string& date) { this->datePublished = date; } // Set the date published
    void setText(const std::string& text); // Set the original text of the document and process term frequencies
    void setAuthors(const std::vector<std::string>& authors) { this->authors = authors; } // Set the list of authors
    void setOrganizations(const std::vector<std::string>& orgs) { this->organizations = orgs; } // Set the list of organizations
    void setPersons(const std::vector<std::string>& persons) { this->persons = persons; } // Set the list of persons
    void setFilePath(const std::string& filePath) { this->filePath = filePath; } // Set the file path of the document
    void setProcessedText(const std::string& processedText); // Set the processed text for the document

private:
    // Private member variables for document metadata and content
    std::string title; // Title of the document
    std::string publication; // Publication associated with the document
    std::string datePublished; // Date when the document was published
    std::string text; // Processed text of the document
    std::string originalText; // Original unprocessed text of the document
    std::vector<std::string> authors; // List of authors
    std::vector<std::string> organizations; // List of organizations mentioned
    std::vector<std::string> persons; // List of persons mentioned
    std::string filePath; // Path to the document file
    
    // Map for storing term frequencies for text analysis
    std::unordered_map<std::string, int> termFrequencies;
};

#endif
