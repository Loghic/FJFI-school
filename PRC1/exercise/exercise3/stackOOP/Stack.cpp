#include "Stack.h"
#include <iostream>
#include <stdexcept>

Stack::Stack(int capacity)
: sp(-1), size(capacity), array(new Data[size])
{
    std::cout << "Constructor with parameter\n";
}

Stack::~Stack()
{
    std::cout << "Destructor!\n";
    delete []array;
    array = nullptr;
}

void Stack::push(Data d)
{
    if (isFull()){
        throw std::logic_error("Pushing into full stack");
    }else{
        sp++;
        this->array[sp] = d;
    }
}

void Stack::pop()
{
    if (isEmpty()){
        throw std::logic_error("Popping empty stack!");
    }else{
        this->array[sp] = 0;
        sp--;
    }
}
Data Stack::top() const
{
    if (!isEmpty()) return array[sp];
    else throw std::logic_error("Accessing top of empty stack");
}