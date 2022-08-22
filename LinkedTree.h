#include "BinarySearchTree.h"
#include "node.h"


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





template <class t>
LinkedTree <t> :: LinkedTree() {
    root = nullptr;
}

template <class t>
LinkedTree <t> :: ~LinkedTree() {
    MakeEmpty();
}

template <class t>
void LinkedTree <t> :: Put(t putMe) {
    InsertNode(this->root, putMe);
}

template <class t>
void LinkedTree <t> :: Remove(t removeMe) {
    FindAndDelete(this->root, removeMe);
}

template <class t>
void LinkedTree <t> :: MakeEmpty() {
    EmptyTree(this->root);
    this->root = nullptr;
}

template <class t>
bool LinkedTree <t> :: IsInTree(t findMe) {
    if (GetAddress(this->root, findMe) == nullptr) {
        return false;
    }
        return true;
}

template <class t>
int LinkedTree <t> :: GetLength() {
    return CountNodes(this->root);
}

template <class t>
void LinkedTree <t> :: Print() {
    RecursivePrint(this->root);
}