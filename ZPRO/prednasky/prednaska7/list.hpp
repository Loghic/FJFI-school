#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream>
using T = int;
// typedef int T; same declaration as example above

const T myNULL = 0;

struct element
{
    T data;
    element* next;
};

struct list
{
    element *head;
    element *sentinel; // end of list aka last element
    size_t length;
};

void make(list& l);
void push_front(list& l, T what);
void push_back(list& l, T what);
void pop_first(list& l);

#endif // !__LIST_HPP__