#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include "Document.h"

template<typename Key, typename Value>
class AVLTree {
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }

    void insert(const Key& key, const Value& value) {
        root = insertHelper(root, key, value);
    }

    Value find(const Key& key) const {
        Node* node = findHelper(root, key);
        if (node) {
            return node->value;
        }
        return Value();
    }

    bool contains(const Key& key) const {
        return findHelper(root, key) != nullptr;
    }
    
    void saveToFile(const std::string& filePath) const {
        std::ofstream outFile(filePath, std::ios::binary);
        if (outFile.is_open()) {
            saveToFileHelper(root, outFile);
            outFile.close();
        }
    }

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
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        int height;

        Node(const Key& k, const Value& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    Node* insertHelper(Node* node, const Key& key, const Value& value) {
        if (!node) {
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insertHelper(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertHelper(node->right, key, value);
        } else {
            // Key exists, update value
            node->value = value;
            return node;
        }

        updateHeight(node);
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* findHelper(Node* node, const Key& key) const {
        if (!node || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return findHelper(node->left, key);
        }
        return findHelper(node->right, key);
    }

    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    void destroy(Node* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    void saveToFileHelper(Node* node, std::ofstream& outFile) const {
        if (node) {
            saveToFileHelper(node->left, outFile);
            outFile << node->key << ";";
            
            // Handle vector<shared_ptr<Document>> specially
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
            
            saveToFileHelper(node->right, outFile);
        }
    }
    
    void updateHeight(Node* node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    template<typename T>
    void serializeValue(const std::vector<T>& vec, std::ofstream& outFile) const;

    template<typename T>
    void deserializeValue(std::vector<T>& vec, const std::string& str);

    // Add this specialization for Document pointers
    template<>
    void deserializeValue(std::vector<std::shared_ptr<Document>>& docs, const std::string& str) {
        std::istringstream iss(str);
        size_t size;
        iss >> size;
        docs.clear();
        
        for (size_t i = 0; i < size; ++i) {
            std::string filePath, title, publication, datePublished, text;
            iss >> filePath >> title >> publication >> datePublished;
            std::getline(iss, text);  // Get the rest of the line as text
            
            auto doc = std::make_shared<Document>(filePath);
            doc->setTitle(title);
            doc->setPublication(publication);
            doc->setDatePublished(datePublished);
            doc->setText(text);
            
            docs.push_back(doc);
        }
    }
};

#endif 