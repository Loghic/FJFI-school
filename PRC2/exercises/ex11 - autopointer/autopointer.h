#ifndef EX11___AUTOPOINTER_AUTOPOINTER_H
#define EX11___AUTOPOINTER_AUTOPOINTER_H

template<typename T>
class AutoPointer{
    T *ptr;
    bool owner; // one and only one autopointer can be owner of an object
public:
    // TODO
    AutoPointer(T *p);
    AutoPointer(AutoPointer<T> &other); // copy constructor
    ~AutoPointer();
    AutoPointer<T>& operator=(AutoPointer<T> &rhs);
    T* operator->();
};

#endif //EX11___AUTOPOINTER_AUTOPOINTER_H
