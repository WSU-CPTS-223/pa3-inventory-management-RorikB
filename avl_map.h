#ifndef AVL_MAP_H
#define AVL_MAP_H

#include <algorithm>
#include <iostream>

using namespace std;

// Custom AVL tree based map using 2 templates
template <typename K, typename V>
class avl_map {
private:
    class Node {
    public:
        K key;
        V value;
        Node* left;
        Node* right;
        int height;

        Node(K newKey, V newValue) : key(newKey), value(newValue), left(nullptr), right(nullptr), height(0) {}
    };

    class Iterator {
    private:
        Node* current; // Current node in the iteration
    public:
        Iterator(Node* node) : current(node) {} // Constructor
        Iterator& operator++() { // Pre-increment operator, in-order traversal
            if (current->right) {
                current = current->right;
                while (current->left) current = current->left;
            } 

            return *this;
        }
    };

    Node* root;
    
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    Node* rightRotate(Node* node) {
        Node* l = node->left; // Left node
        Node* lr = l->right; // Left-Right node
        l->right = node; // Left-Right becomes the old node
        node->left = lr; // Old node's left becomes Left-Right

        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        l->height = std::max(getHeight(l->left), getHeight(l->right)) + 1;
        return l;
    }
    Node* leftRotate(Node* node) {
        Node* r = node->right; // Right node
        Node* rl = r->left; // Right-Left node
        r->left = node; // Right-Left becomes the old node
        node->right = rl; // Old node's right becomes Right-Left

        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        r->height = std::max(getHeight(r->left), getHeight(r->right)) + 1;
        return r;
    }
    
    Node* insert(Node* node, const K& key, const V& value) {
        if (!node) return new Node(key, value); // if node is null, create a new node
        if (key < node->key)
            node->left = insert(node->left, key, value); // Recursive Left
        else if (key > node->key)
            node->right = insert(node->right, key, value); // Recursive Right
        else {
            node->value = value; // Update value if key already exists
            return node;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* search(Node* node, const K& key) { // Searches for a key in the tree
        if (!node || node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    // Removes Key-Value pair from the tree
    void erase(Node* node, const K& key) {
        if (!node) return; // Key not found
        if (key < node->key)
            node->left = erase(node->left, key); // Recursive Left
        else if (key > node->key)
            node->right = erase(node->right, key); // Recursive Right
        else {
            // Node with only one child or no child
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) { // No child case
                    temp = node;
                    node = nullptr;
                } else { // One child case
                    *node = *temp; // Copy the contents of the non-empty child
                }
                delete temp;
            } else {
                // Node with two children: Get the inorder successor, smallest in the right subtree
                Node* temp = node++; // Find minimum in the right subtree, iterator ++
                node->key = temp->key; // Copy the inorder successor's data to this node
                node->value = temp->value;
                node->right = erase(node->right, temp->key); // Delete the inorder successor
            }
        }

        if (!node) return; // If the tree had only one node then return
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0)
            return;
        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return;
        }
        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0)
            return;
        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return;
        }
        return;
    }

public:
    avl_map() : root(nullptr) {}

    void insert(K key, V value) {
        root = insert(root, key, value);
    }
    
    void erase(const K& key) {
        erase(root, key);
    }

    // Return an iterator from find just like std::map
    Iterator find(const K& key) {
        Node* result = search(root, key);
        if (result) {
            return Iterator(result);
        } else {
            return nullptr; // Return null iterator if not found
        }
    }
};

#endif 