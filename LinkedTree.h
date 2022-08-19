#include "BinarySearchTree.h"

#include <iostream>

using namespace std;


// Node definition:
template <class t>
struct node {
    t info;
    node * left;
    node * right;
};



template <class t>
class LinkedTree : public BinarySearchTree <t> {

public:

    // Constructor
    LinkedTree();
    ~LinkedTree();

    // Transformers
    virtual void Put(t);
    virtual void Remove(t);
    virtual void MakeEmpty();

    // Observers
    virtual bool IsInTree(t);
    virtual int GetLength();

    // Print for testing
    void Print();

protected:

    // Member variables
    node <t> * root;
};






// PrintTree()

template <class t>
void RecursivePrint(node <t> * printMe) {
    if (printMe == nullptr) {
        return;
    }
    RecursivePrint(printMe->left);
    cout << printMe->info << ' ';
    RecursivePrint(printMe->right);
}

template <class t>
void LinkedTree <t> :: Print() {
    RecursivePrint(this->root);
}







// Constructor

template <class t>
LinkedTree <t> :: LinkedTree() {
    root = nullptr;
}

template <class t>
LinkedTree <t> :: ~LinkedTree() {
    MakeEmpty();
}









// MakeEmpty()

template <class t>
void EmptyTree(node <t> * emptyMe) {
    if (emptyMe == nullptr) {
        return;
    }
    EmptyTree(emptyMe->left);
    EmptyTree(emptyMe->right);
    delete emptyMe;
}

template <class t>
void LinkedTree <t> :: MakeEmpty() {
    EmptyTree(this->root);
    this->root = nullptr;
}








// Remove()

/* Helper functions for recursive processing. */
template <class t> void FindAndDelete(node <t> * & tree, t findMe);
template <class t> void DeleteNode(node <t> * & deleteMe);
template <class t> t GetGreatestValue(node <t> * tree);

/* Class method. */
template <class t>
void LinkedTree <t> :: Remove(t removeMe) {
    FindAndDelete(this->root, removeMe);
}

template <class t>
void FindAndDelete(node <t> * & tree, t findMe) {
    // Not in tree.
    if (tree == nullptr) {
        return;
    }
    // Found it.
    if (findMe == tree->info) {
        DeleteNode(tree);
    }
    // Keep searching.
    else {
        // Go left.
        if (findMe < tree->info) {
            FindAndDelete(tree->left, findMe);
        }
        // Go right.
        if (findMe > tree->info) {
            FindAndDelete(tree->right, findMe);
        }
    }
}

template <class t>
void DeleteNode(node <t> * & deleteMe) {
    
    node <t> * deletePointer = deleteMe;

    // COND -- deleteMe has 0 or 1 child nodes.
    if (deleteMe->left == nullptr) {
        deleteMe = deleteMe->right;
        delete deletePointer;
    }
    else if (deleteMe->right == nullptr) {
        deleteMe = deleteMe->left;
        delete deletePointer;
    }

    // COND -- deleteMe has 2 child nodes.
    else {
        t newValue = GetGreatestValue(deleteMe->left);
        deleteMe->info = newValue;
        FindAndDelete(deleteMe->left, newValue);
    }
}

template <class t>
t GetGreatestValue(node <t> * tree) {
    /* Traverse to the right in tree until reaching a node with no right child. This node has the greatest value in the tree. */
    while (tree->right != nullptr) {
        tree = tree->right;
    }
    return tree->info;
}









// GetLength()

/* Helper function to process nodes recursively. */
template <class t>
int CountNodes(node <t> * treeRoot) {
    if (treeRoot == nullptr) {
        return 0;
    }
    else {
        return 1 + CountNodes(treeRoot->left) + CountNodes(treeRoot->right);
    }
}

template <class t>
int LinkedTree <t> :: GetLength() {
    return CountNodes(this->root);
}








// IsInTree()

template <class t>
bool RecursiveSearch(node <t> * treeRoot, t findMe) {
    // Base cases.
    if (treeRoot == nullptr) {
        return false;
    }
    if (treeRoot->info == findMe) {
        return true;
    }
    // Recursive cases -- keep searching.
    if (findMe < treeRoot->info) {
        return RecursiveSearch(treeRoot->left, findMe);
    }
    else {
        return RecursiveSearch(treeRoot->right, findMe);
    }
}

template <class t>
bool LinkedTree <t> :: IsInTree(t findMe) {
    return RecursiveSearch(this->root, findMe);
}








// Put()

/* Helper function to process nodes recursively. */
template <class t>
void InsertNode(node <t> * & treeRoot, t insertMe) {

    // Found insertion position.
    if (treeRoot == nullptr) {
        treeRoot = new node <t>;
        treeRoot->right = nullptr;
        treeRoot->left = nullptr;
        treeRoot->info = insertMe;
    }
    // Already in tree -- exit.
    else if (treeRoot->info == insertMe) {
        return;
    }
    // Keep searching.
    else {
        if (insertMe < treeRoot->info) {
            InsertNode(treeRoot->left, insertMe);
        }
        else {
            InsertNode(treeRoot->right, insertMe);
        }
    }
}

template <class t>
void LinkedTree <t> :: Put(t putMe) {
    InsertNode(this->root, putMe);
}