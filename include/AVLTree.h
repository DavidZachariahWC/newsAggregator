#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include "Document.h"

// AVLTree class template definition for managing a balanced binary search tree
template<typename Key, typename Value>
class AVLTree {
public:
    // Constructor initializes the root to nullptr
    AVLTree() : root(nullptr) {}

    // Destructor cleans up memory used by tree nodes
    ~AVLTree() { destroy(root); }

    // Inserts a key-value pair into the tree
    void insert(const Key& key, const Value& value) {
        root = insertHelper(root, key, value);
    }

    // Finds the value associated with a key
    Value find(const Key& key) const {
        Node* node = findHelper(root, key);
        if (node) {
            return node->value; // Return the value if the key is found
        }
        return Value(); // Return default value if key is not found
    }

    // Checks if the tree contains a key
    bool contains(const Key& key) const {
        return findHelper(root, key) != nullptr;
    }
    
    // Saves the tree to a file in a serialized format
    void saveToFile(const std::string& filePath) const {
        std::ofstream outFile(filePath, std::ios::binary);
        if (outFile.is_open()) {
            saveToFileHelper(root, outFile);
            outFile.close();
        }
    }

    // Loads the tree from a file in a serialized format
    void loadFromFile(const std::string& filePath) {
        destroy(root); // Clear any existing data
        root = nullptr;

        std::ifstream inFile(filePath, std::ios::binary);
        if (inFile.is_open()) {
            std::string line;
            while (std::getline(inFile, line)) {
                size_t pos = line.find(';');
                if (pos != std::string::npos) {
                    Key key = line.substr(0, pos); // Extract the key
                    Value value;
                    deserializeValue(value, line.substr(pos + 1)); // Deserialize the value
                    insert(key, value);
                }
            }
            inFile.close();
        }
    }

private:
    // Node structure for AVL tree
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        int height;

        // Node constructor initializes key, value, and pointers
        Node(const Key& k, const Value& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root; // Root node of the AVL tree

    // Helper function to insert a key-value pair and maintain balance
    Node* insertHelper(Node* node, const Key& key, const Value& value) {
        if (!node) {
            return new Node(key, value); // Create a new node if the position is empty
        }

        if (key < node->key) {
            node->left = insertHelper(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertHelper(node->right, key, value);
        } else {
            // If the key exists, update the value
            node->value = value;
            return node;
        }

        // Update the height and balance the node
        updateHeight(node);
        int balance = getBalance(node);

        // Perform rotations based on balance factor
        if (balance > 1 && key < node->left->key) { // Left-Left Case
            return rotateRight(node);
        }
        if (balance < -1 && key > node->right->key) { // Right-Right Case
            return rotateLeft(node);
        }
        if (balance > 1 && key > node->left->key) { // Left-Right Case
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) { // Right-Left Case
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node; // Return the balanced node
    }

    // Helper function to find a node by key
    Node* findHelper(Node* node, const Key& key) const {
        if (!node || node->key == key) {
            return node; // Return the node if found
        }

        if (key < node->key) {
            return findHelper(node->left, key); // Search in the left subtree
        }
        return findHelper(node->right, key); // Search in the right subtree
    }

    // Gets the height of a node
    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    // Gets the balance factor of a node
    int getBalance(Node* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Rotates the subtree to the right
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Rotates the subtree to the left
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Destroys the tree by deallocating all nodes
    void destroy(Node* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    // Helper function to save the tree to a file in order
    void saveToFileHelper(Node* node, std::ofstream& outFile) const {
        if (node) {
            saveToFileHelper(node->left, outFile); // Save left subtree
            outFile << node->key << ";";
            
            // Special handling for vectors of shared pointers to Documents
            if constexpr (std::is_same_v<Value, std::vector<std::shared_ptr<Document>>>) {
                const auto& docs = node->value;
                outFile << docs.size();
                for (const auto& doc : docs) {
                    outFile << " " << doc->getFilePath()
                            << " " << doc->getTitle()
                            << " " << doc->getPublication()
                            << " " << doc->getDatePublished()
                            << " " << doc->getText();
                }
            } else {
                outFile << node->value;
            }
            outFile << "\n";
            
            saveToFileHelper(node->right, outFile); // Save right subtree
        }
    }
    
    // Updates the height of a node based on its children
    void updateHeight(Node* node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    // Deserializes a value from a string (specialized for Document pointers)
    template<>
    void deserializeValue(std::vector<std::shared_ptr<Document>>& docs, const std::string& str) {
        std::istringstream iss(str);
        size_t size;
        iss >> size;
        docs.clear();
        
        for (size_t i = 0; i < size; ++i) {
            std::string filePath, title, publication, datePublished, text;
            iss >> filePath >> title >> publication >> datePublished;
            std::getline(iss, text); // Get the rest of the line as text
            
            auto doc = std::make_shared<Document>(filePath);
            doc->setTitle(title);
            doc->setPublication(publication);
            doc->setDatePublished(datePublished);
            doc->setText(text);
            
            docs.push_back(doc); // Add the deserialized Document to the vector
        }
    }
};

#endif
