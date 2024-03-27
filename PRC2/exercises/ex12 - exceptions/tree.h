#ifndef EX12___EXCEPTIONS_TREE_H
#define EX12___EXCEPTIONS_TREE_H

#include "node.h"
#include "iostream"

#include "treeException.h"

using namespace std;

template <typename T>
class Tree {
    Node<T> *root;
    void insertIntoSubTree(Node<T> *&r, T &data);
    void printSubTree(Node<T> *r);
    void cleanSubtree(Node<T> *&r);
    Node<T>* findInSubTree(Node<T> *r, Node<T> *&parent, T &what);
    void removeLeaf(Node<T> *parent, Node<T> *leaf);
    void removeInBranch(Node<T> *parent, Node<T> *child);
public:
    Tree() : root(nullptr) {}
    ~Tree() {clean();}

    void clean(){
        cleanSubtree(root);
        root = nullptr;
    }

    void insert(T d) {
        insertIntoSubTree(root, d);
    }
    void print(){
        printSubTree(root);
    }

    bool contains(T what)
    {
        Node<T> *dummy = nullptr;
        dummy = findInSubTree(root, dummy, what);
        return dummy;
    }

    void remove(T d);
};

template <typename T>
// we have to pass r by reference
void Tree<T>::insertIntoSubTree(Node<T> *&r, T &data)
{
    // checks if r is not a null ptr
    // r == nullptr
    if (!r){
//        try {
//            r = new Node<T>(data); // new can throw bad alloc
//        } catch (bad_alloc &e){
//            // converting library exception to my exception
//            throw TreeException("Memory allocation failed");
//        }

        r = new(nothrow) Node<T>(data);
        if (!r){
            throw TreeException("Memory allocation failed");
        }

        return;
    }

    if (r->data == data) {
        throw TreeException("Value is already in the tree");
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

template<typename T>
void Tree<T>::cleanSubtree(Node<T> *&r)
{
    if (r){
        cleanSubtree(r->left);
        cleanSubtree(r->right);
        delete r;
        r = nullptr;
    }
}
template<typename T>
Node<T>* Tree<T>::findInSubTree(Node<T> *r, Node<T> *&parent, T &what)
{
    if (!r){
        return nullptr;
    }
    if(r->data == what){
        return r;
    }
    parent = r;
    if(what > r->data){
        return findInSubTree(r->right, parent, what);
    }else{
        return findInSubTree(r->left, parent, what);
    }

}

template<typename T>
void Tree<T>::removeLeaf(Node<T> *parent, Node<T> *leaf)
{
    if (parent) {
        if (parent->left == leaf) {
            parent->left = nullptr;
        } else if (parent->right == leaf) {
            parent->right = nullptr;
        }
    }else{ //tree with just one node
        root = nullptr;
    }
    delete leaf;
    leaf = nullptr;

}

template<typename T>
void Tree<T>::removeInBranch(Node<T> *parent, Node<T> *child)
{
    Node<T> *grandchild = child->left ? child->left : child->right;

    if (parent){
        if (parent->right == child){
            parent->right = grandchild;
        }else if(parent->left == child){
            parent->left = grandchild;
        }
    }else{
        root = grandchild;
    }
    delete child;
    child = nullptr;
}

template<typename T>
void Tree<T>::remove(T d)
{
    Node<T> *p, *parent = nullptr;
    p = findInSubTree(root, parent, d);
    if (!p){
        //adding exception
        throw TreeException("Element to be removed is not in the tree");
    }
    //no children
    if (!p->left && !p->right){
        removeLeaf(parent, p);
    }
        //one child
    else if (!p->left || !p->right){
        removeInBranch(parent,p);
    }
        //two children
    else if(p->left && p->right) {
        Node<T> *q = p->right;
        parent = p;
        while (q->left) {
            parent = q;
            q = q->left;
        }

        p->data = q->data;
        if (q->right) {
            removeInBranch(parent, q);
        } else {
            removeLeaf(parent, q);
        }
    }
}

#endif //EX12___EXCEPTIONS_TREE_H
