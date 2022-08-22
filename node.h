#include <iostream>
using namespace std;


/* All the functionality to work with a binary search tree is in this file. The LinkedTree class adds no functionality, but gives an object-oriented programming interface that is easier to work with. */


template <class t>
struct node {
    t info;
    node * left;
    node * right;
};





template <class t>
void InsertNode(node <t> * & treeRoot, t insertMe) {
    /* Binary search. */

    // COND -- Found insertion position.
    if (treeRoot == nullptr) {
        treeRoot = new node <t>;
        treeRoot->right = nullptr;
        treeRoot->left = nullptr;
        treeRoot->info = insertMe;
    }
    // COND -- Already in tree.
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
node <t> * GetAddress(node <t> * treeRoot, t findMe) {
    /* Binary search.
    Return nullptr if findMe does not match any node in tree. */

    // Base case.
    if ((treeRoot == nullptr) or (treeRoot->info == findMe)) {
        return treeRoot;
    }

    // Recursive case -- keep searching.
    if (findMe < treeRoot->info) {
        return GetAddress(treeRoot->left, findMe);
    }
    else {
        return GetAddress(treeRoot->right, findMe);
    }
}









/* Deleting a tree node is divided into 3 procedures -- find, then delete, then replace if necessary. */

template <class t> void FindAndDelete(node <t> *, t);
template <class t> void DeleteNode(node <t> * &);
template <class t> t GetGreatestValue(node <t> *);

template <class t>
void FindAndDelete(node <t> * tree, t findMe) {
    node <t> * deleteAddress = GetAddress(tree, findMe);
    // COND -- findMe is not in tree.
    if (deleteAddress == nullptr) {
        return;
    }
    DeleteNode(deleteAddress);
}

template <class t>
void DeleteNode(node <t> * & deleteMe) {
    /* Rearrange node pointers depending on how many child nodes deleteMe has. */
    
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
        /* Get the greatest value in deleteMe's left subtree, use it to replace deleteMe, then repeat the delete process on the node we took from the subtree. */
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











// Little functions:

template <class t>
int CountNodes(node <t> * treeRoot) {
    if (treeRoot == nullptr) {
        return 0;
    }
    return 1 + CountNodes(treeRoot->left) + CountNodes(treeRoot->right);
}


template <class t>
void RecursivePrint(node <t> * printMe) {
    /* Print left subtree, self, right subtree.  Effectively this prints all tree elements in order. */
    if (printMe == nullptr) {
        return;
    }
    RecursivePrint(printMe->left);
    cout << printMe->info << ' ';
    RecursivePrint(printMe->right);
}


template <class t>
void EmptyTree(node <t> * emptyMe) {
    /* Delete left node, right node, self. */
    if (emptyMe == nullptr) {
        return;
    }
    EmptyTree(emptyMe->left);
    EmptyTree(emptyMe->right);
    delete emptyMe;
}