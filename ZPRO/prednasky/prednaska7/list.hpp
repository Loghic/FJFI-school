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
void push_behind(list& l, T what, element* whichOne);
void pop_first(list& l);
//void delete_behind(list& l, element* which);
void my_delete(list& l, element* which);
void empty(list& l);
bool is_Empty(list& l);
void delete_list(list& l);
size_t len_list(list& l);
element* find(T what);
void my_print(list& l);
element* find_the_lowest(list& l);
element* find_the_(list& l);


#endif // !__LIST_HPP__