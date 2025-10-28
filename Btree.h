#ifndef BTREE_H
#define BTREE_H 

// B-tree class 
class BTreeNode {
private:
    int *keys;      
    int t;          
    BTreeNode **C;  
    int n;          
    bool leaf;     
public:
    BTreeNode(int _t, bool _leaf); 
    void traverse();
    BTreeNode *search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *y);
    friend class BTree;
};

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