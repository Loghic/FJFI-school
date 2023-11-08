#ifndef HW3_ELEMENT_H
#define HW3_ELEMENT_H

typedef int Data;

#include <iostream>

class Element{
    Element *prev;
    Element *next;
    Data data;
public:
    Element(Data d)
            : prev(nullptr), next(nullptr),
              data(d)
    {}
    Element()
            : prev(nullptr), next(nullptr)
    {}
    void setData(Data d){data = d;}
    Data getData() const{return data;}
    void print() const{
        std::cout << getData();
    }
    void printLn() const{
        print();
        std::cout << std::endl;
    }
    friend class List;
};

#endif //HW3_ELEMENT_H
