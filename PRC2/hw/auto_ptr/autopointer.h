#ifndef EX11___AUTOPOINTER_AUTOPOINTER_H
#define EX11___AUTOPOINTER_AUTOPOINTER_H

#include "iostream"
#include "debug.h"

using namespace std;

template<typename T>
class AutoPointer{
    T *ptr;
    bool owner; // one and only one AutoPointer can be owner of an object
public:
    AutoPointer(T *p);// constructor
    AutoPointer(AutoPointer<T> &other); // copy constructor
    ~AutoPointer();

    AutoPointer<T>& operator=(AutoPointer<T> &rhs);

    T* operator->();
};

//constructor
template<typename T>
AutoPointer<T>::AutoPointer(T *p)
    :ptr(p), owner(true)
{
#ifdef DEBUG
        cout << "Constructor\n";
#endif
}

template<typename T>
AutoPointer<T>::AutoPointer(AutoPointer<T> &other)
: ptr(other.ptr), owner(other.owner)
{
#ifdef DEBUG
    cout << "Copy constructor\n";
#endif
    other.owner = false;
}

template<typename T>
AutoPointer<T>::~AutoPointer()
{
#ifdef DEBUG
    cout << "Destructor\n";
#endif
    if (owner && ptr){
        delete ptr;
    }
    ptr = nullptr;
}

template<typename T>
AutoPointer<T> &AutoPointer<T>::operator=(AutoPointer<T> &rhs)
{
#ifdef DEBUG
    cout << "Assigment operator\n";
#endif
    if (this != &rhs){
        if (ptr && owner){
            delete ptr;
        }
        ptr = rhs.ptr;
        owner = rhs.owner;
        rhs.owner = false;
    }
    return *this;
}

template<typename T>
T *AutoPointer<T>::operator->()
{
#ifdef DEBUG
    cout << "Sub-pointer\n";
#endif
    return ptr;
}





#endif //EX11___AUTOPOINTER_AUTOPOINTER_H
