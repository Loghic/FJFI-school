#ifndef __linkedlist_HPP__
#define __linkedlist_HPP__

#include "element.hpp"

struct List;

List* createList();
void pushFront(List *l, Data d);
Data popFront(List *l);
void pushBack(List *l, Data d);
Data popBack(List *l);
void print(List *l);
void findChange(List *l, Data d, Data newD);
Data getSize(List *l);



#endif