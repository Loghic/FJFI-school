#ifndef LECTURE4_SEZNAM_H
#define LECTURE4_SEZNAM_H

#include "iostream"


template<class T>
struct Element
{
    T data;
    Element* next;
    Element(T data, Element* next);
    ~Element() {counter--;}
    static size_t counter;
};

template<class T>
Element<T>::Element(T data, Element<T> *next) : data(data), next(next)
{
    counter++;
}

//Template of static attribute
template<class T>
size_t Element<T>::counter = 0;

template<class T>
class Seznam {
public:
    Seznam();
    void pushFront(T what);
    void print(){
        while (head != sentinel){
            std::cout << head->data << ", ";
            head = head->next;
        }
        std::cout << std::endl;
    }
    Element<T> getHead() const {return *head;}
private:
    Element<T> *head, *sentinel;
};

template<class T>
Seznam<T>::Seznam()
{
    head = sentinel = new Element<T>{0, nullptr};
}

template<class T>
void Seznam<T>::pushFront(T what)
{
    head = new Element<T>{what, head};
}


#endif //LECTURE4_SEZNAM_H
