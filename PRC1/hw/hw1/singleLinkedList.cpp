#include "singleLinkedList.h"

void makeList(myList& l)
{
    l.head = l.sentinel = new myElement {0, nullptr};
    l.length = 0;
}

void pushFront(myList& l, T data)
{
    l.head = new myElement {data, l.head};
    l.length++;
}

void pushBack(myList& l, T data)
{
    l.sentinel->data = data;
    l.sentinel->next = new myElement{0, nullptr};
    l.sentinel = l.sentinel->next;
    l.length++;
}

void pushBehind(myList& l, T data, myElement* where)
{
    where->next = new myElement {data, where->next};
    l.length++;
}

void popFirst(myList &l)
{
    myElement* tmp = l.head;
    l.head = l.head->next;
    delete tmp;
    l.length--;
}

void deleteBehind(myList &l, myElement* which)
{
    auto tmp = which->next;
    if (tmp == l.sentinel) return;
    which->next = tmp->next;
    delete tmp;
    l.length--;
}

void deleteElement(myList &l, myElement* which)
{
    if (which->next == l.sentinel){ // if deleted element is last
        l.sentinel = which;
        delete which->next;
        which->next = nullptr;
        l.length--;
    }else{
        which->data = which->next->data;
        deleteBehind(l, which);
    }
}

myIterator find(myList &l, T what)
{
    l.sentinel->data = what;
    myElement* tmp = l.head;
    while(tmp->data != what){
        tmp = tmp->next;
    }
    return myIterator{tmp, &l};
}

void myPrint(myList &l)
{
    for(myIterator i = myBegin(&l); !isEqual(i,myEnd(&l)); go_to_next(i)){
        cout << returnValue(i) << ", ";
    }
    cout << endl;
}

bool isEmpty(myList &l)
{
    return l.length == 0;
}

int listLength(myList &l)
{
    return l.length;
}
void empty(myList &l)
{
    while(!isEmpty(l)){
        popFirst(l);
    }
}
void deleteList(myList &l)
{
    empty(l);
    delete l.head;
}

myElement* findLowest(myList &l)
{
    myElement* lowest = l.head;
    for (myElement* tmp = l.head; tmp != l.sentinel; tmp = tmp->next){
        if(tmp->data < lowest->data){
            lowest = tmp;
        }
    }
    return lowest;
}
myElement* findBiggest(myList &l)
{
    myElement* biggest = l.head;
    for (myElement* tmp = l.head; tmp != l.sentinel; tmp = tmp->next){
        if(tmp->data < biggest->data){
            biggest = tmp;
        }
    }
    return biggest;
}
void sort(myList &l)
{
    myList tmp;
    makeList(tmp);
    while (!isEmpty(l)){
        myElement* lowest = findLowest(l);
        pushBack(tmp, lowest->data);
        deleteElement(l, lowest);
    }
    swap(l.head, tmp.head);
    swap(l.sentinel, tmp.sentinel);
    swap(l.length, tmp.length);
    deleteList(tmp);
}

myIterator makeIterator(myList *l, myElement *element)
{
    return myIterator{element, l};
}
bool go_to_next(myIterator& i)
{
    if (i.actual == i.l->sentinel){
        return false;
    }
    i.actual = i.actual->next;
    return true;
}

myIterator myBegin(myList *l)
{
    return myIterator{l->head,l};
}

myIterator myEnd(myList *l)
{
    return myIterator{l->sentinel, l};
}

T returnValue(myIterator i)
{
    return i.actual->data;
}

void setValue(myIterator& i, T value)
{
    i.actual->data = value;
}
bool isEqual(myIterator i1, myIterator i2)
{
    return i1.actual == i2.actual;
}