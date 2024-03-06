#ifndef EX9___BINARY_LOOKUP_TREE_OF_TYPE_T_NODE_H
#define EX9___BINARY_LOOKUP_TREE_OF_TYPE_T_NODE_H

#include "iostream"


template<typename T>
class Node{
    T data;
    int key;
    Node<T> *left;
    Node<T> *right;
public:
    Node(T d) : data(d), left(nullptr), right(nullptr) {}

    T getData() const {return data;}
    void setData(const T val) {data = val;}

    void print() const{
        std::cout << data;
    }
    void printLine() const{
        print();
        std::cout << std::endl;
    }

    //declaring a template class as a friend
    template<typename X> friend class Tree;
};


template <typename T>
std::ostream& operator<<(std::ostream &os, Node<T> &n)
{
    os << n.getData();
    return os;
}


#endif //EX9___BINARY_LOOKUP_TREE_OF_TYPE_T_NODE_H
