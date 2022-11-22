#include <iostream>
#include "linkedList.hpp"

using namespace std;
struct List{
    element* head; // first
    element* sentinel; // last
    size_t length; // counter
};

List* createList()
{
    List *l = new(nothrow) List;
    if (!l){
        return nullptr;
    }
    l->head = new element;
    l->head->next = nullptr;
    l->sentinel = l->head;
    l->length = 0;
    return l;
}

bool pushFront(List *l, Data d)
{
    element *ptr = new(std::nothrow) element;
    if(!ptr){               // if (ptr == nullptr)
        return false;
    }
    ptr->data = d;
    ptr->next = l->head;
    l->head = ptr;
    l->length++;
    return true;
}

bool isEmpty(List *l)
{
    return (l->length == 0);
}

bool popFront(List *l)
{
    if(isEmpty(l)){
        return false;
    }
    element *tmp = l->head;
    l->head = tmp->next;
    delete tmp;
    l->length--;
    return true;
}

Data front(List *l)
{
    return l->head->data;
}

void print(List *l)
{
    for (element *i = l->head; i != l->sentinel; i = i->next){
        cout << i->data << " ";
    }
    if(isEmpty(l)){
        cout << "List is empty";
    }
    cout << "\n"; 
}

void clean(List *l)
{
    while (!isEmpty(l)){
        popFront(l);
    }
}

void destroyList(List *&l){
    clean(l);
    delete l->head;
    delete l;
}

element* find(List *l, Data d)
{
    element *tmp = l->head;
    l->sentinel->data = d;
    while (tmp->data != d){
        tmp = tmp->next;
    }
    return (tmp == l->head ? nullptr : tmp);   
}

//removes element after element where
void removeAfter(List *l, element *where)
{
    element *tmp = where->next;
    if (tmp == l->sentinel){
        l->sentinel = where;
        where->next = tmp->next;
    }else{
        where->next = tmp->next;
    }
    delete tmp;
    l->length--;
}

bool remove(List *l, Data d)
{
    element *tmp = find(l, d);
    if (!tmp){
        return false;
    }
    tmp->data = tmp->next->data;
    removeAfter(l, tmp);
    return true;
}

bool pushBack(List *l, Data d)
{
    element *ptr = new(std::nothrow) element;
    if(!ptr){               // if (ptr == nullptr)
        return false;
    }
    l->sentinel->data = d;
    ptr->next = nullptr;
    l->sentinel->next = ptr;
    l->sentinel = ptr;
    l->length++;
    return true;
}
