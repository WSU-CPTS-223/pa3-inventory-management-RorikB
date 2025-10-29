#ifndef BTREE_H
#define BTREE_H 

#include "BtreeNode.h"

// B-tree class 
class BTree {
private:
    BTreeNode *root; 
    int t;      
public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }
    void traverse() {
        if (root != nullptr) {
            root->traverse();
        }
    }
    BTreeNode *search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }
    void insert(int k);
};

#endif