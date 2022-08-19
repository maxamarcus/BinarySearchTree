// BinarySearchTree ABC


template <class t>
class BinarySearchTree {

public:

    // TRANSFORMERS
    virtual void Put(t) = 0;
    virtual void Remove(t) = 0;
    virtual void MakeEmpty() = 0;

    // OBSERVERS
    virtual bool IsInTree(t) = 0;
    virtual int GetLength() = 0;
};