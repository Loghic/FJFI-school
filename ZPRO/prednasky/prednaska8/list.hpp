#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream>
#include <string>
using namespace std;
using T = int; // str
// typedef int T; same declaration as example above

const T myNULL = 0; // ""

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

struct my_iterator
{
    element * acctual;
    list * l;
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
my_iterator find(list *l, T what);
void my_print(list& l);
element* find_the_lowest(list& l);
element* find_the_biggest(list& l);
void sort(list& l);
//-----------------------------------------------------//
my_iterator make_iterator(list *l, element *Element);
bool go_to_next(my_iterator& i);
my_iterator begin(list *l);
my_iterator end(list *l);
T return_value(my_iterator i);
void set_value(my_iterator& i, T value);
bool is_equal(my_iterator i1, my_iterator i2);

#endif // !__LIST_HPP__