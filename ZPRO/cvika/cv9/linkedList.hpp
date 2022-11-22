#ifndef __linkedList_HPP__
#define __linkedList_HPP__

#include "element.hpp"

struct List; // forward decleration

List* createList();
bool pushFront(List *l, Data d);
bool popFront(List *l);
bool isEmpty(List *l);
Data front(List *l);
void print(List *l);
void clean(List *l);
void destroyList(List *&l);
element* find(List *l, Data d);
bool remove(List *l, Data d);
bool pushBack(List *l, Data d);


#endif // __linkedList_HPP__

