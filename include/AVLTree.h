#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include "Document.h"

// AVLTree class implementing a self-balancing binary search tree with persistence
template<typename Key, typename Value>
class AVLTree {
public:
    AVLTree() : root(nullptr) {} // Constructor initializes an empty tree
    ~AVLTree() { destroy(root); } // Destructor to free allocated memory

    // Inserts a key-value pair into the tree
    void insert(const Key& key, const Value& value) {
        root = insertHelper(root, key, value);
    }

    // Finds a value associated with a given key
    Value find(const Key& key) const {
        Node* node = findHelper(root, key);
        if (node) {
            return node->value;
        }
        return Value();
    }

    // Checks if a key exists in the tree
    bool contains(const Key& key) const {
        return findHelper(root, key) != nullptr;
    }
    
    // Saves the tree to a file for persistence
    void saveToFile(const std::string& filePath) const {
        std::ofstream outFile(filePath, std::ios::binary);
        if (outFile.is_open()) {
            saveToFileHelper(root, outFile);
            outFile.close();
        }
    }

    // Loads a tree from a file for persistence
    void loadFromFile(const std::string& filePath) {
        destroy(root);
        root = nullptr;

        std::ifstream inFile(filePath, std::ios::binary);
        if (inFile.is_open()) {
            std::string line;
            while (std::getline(inFile, line)) {
                size_t pos = line.find(';');
                if (pos != std::string::npos) {
                    Key key = line.substr(0, pos);
                    Value value;
                    deserializeValue(value, line.substr(pos + 1));
                    insert(key, value);
                }
            }
            inFile.close();
        }
    }

private:
    // Node structure representing elements in the AVL tree
    struct Node {
        Key key; // Key for ordering
        Value value; // Value associated with the key
        Node* left; // Left subtree
        Node* right; // Right subtree
        int height; // Height of the node

        Node(const Key& k, const Value& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root; // Root of the AVL tree

    // Recursive helper for insertion
    Node* insertHelper(Node* node, const Key& key, const Value& value);

    // Recursive helper for finding a key
    Node* findHelper(Node* node, const Key& key) const;

    // Gets the height of a node
    int getHeight(Node* node) const;

    // Gets the balance factor of a node
    int getBalance(Node* node) const;

    // Rotations for rebalancing
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);

    // Recursive helper for deleting nodes and freeing memory
    void destroy(Node* node);

    // Recursive helper for saving the tree to a file
    void saveToFileHelper(Node* node, std::ofstream& outFile) const;

    // Updates the height of a node
    void updateHeight(Node* node);

    // Serializes and deserializes values for persistence
    template<typename T>
    void serializeValue(const std::vector<T>& vec, std::ofstream& outFile) const;

    template<typename T>
    void deserializeValue(std::vector<T>& vec, const std::string& str);

    // Specialization for deserializing vector of shared_ptr<Document>
    template<>
    void deserializeValue(std::vector<std::shared_ptr<Document>>& docs, const std::string& str);
};

#endif
