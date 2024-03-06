#ifndef EX9___BINARY_LOOKUP_TREE_OF_TYPE_T_TREE_H
#define EX9___BINARY_LOOKUP_TREE_OF_TYPE_T_TREE_H

#include "node.h"

template <typename T>
class Tree {
    Node<T> *root;
    void insertIntoSubTree(Node<T> *&r, T &data);
    void printSubTree(Node<T> *r);
public:
    Tree() : root(nullptr) {}
    void insert(T d) {
        insertIntoSubTree(root, d);
    }
    void print(){
        printSubTree(root);
    }
};

template <typename T>
// we have to pass r by reference
void Tree<T>::insertIntoSubTree(Node<T> *&r, T &data)
{
    // checks if r is not a null ptr
    // r == nullptr
    if (!r){
        r = new Node<T>(data);
        return;
    }

    if (r->data == data) {
        return;
    }

    if(r->data < data){
        insertIntoSubTree(r->right, data);
    }else{
        insertIntoSubTree(r->left, data);
    }

}

template<typename T>
void Tree<T>::printSubTree(Node<T> *r)
{
    if (r) {
        printSubTree(r->left);
        r->printLine();
        printSubTree(r->right);
    }
}

#endif //EX9___BINARY_LOOKUP_TREE_OF_TYPE_T_TREE_H
