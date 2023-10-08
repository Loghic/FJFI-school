#ifndef HW1_SINGLELINKEDLIST_H
#define HW1_SINGLELINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;

using T = int;

struct myElement{
    T data = 0;
    myElement* next;
};

struct myList{
    myElement* head;
    myElement* sentinel;
    int length = 0;
};

struct myIterator{
    myElement* actual;
    myList* l;
};

void makeList(myList& l);

void pushFront(myList& l, T data);
void pushBack(myList& l, T data);
void pushBehind(myList& l, T data, myElement* where);
void popFirst(myList &l);
void deleteElement(myList &l, myElement* which);
void deleteBehind(myList &l, myElement* which);

myIterator find(myList &l, T what);
void myPrint(myList &l);
bool isEmpty(myList &l);
int listLength(myList &l);
void empty(myList &l);
void deleteList(myList &l);

myElement* findLowest(myList &l);
myElement* findBiggest(myList &l);
void sort(myList &l);

myIterator makeIterator(myList *l, myElement *element);
bool go_to_next(myIterator& i);
myIterator myBegin(myList *l);
myIterator myEnd(myList *l);
T returnValue(myIterator i);
void setValue(myIterator& i, T value);
bool isEqual(myIterator i1, myIterator i2);

#endif //HW1_SINGLELINKEDLIST_H
