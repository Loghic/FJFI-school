#include "linkedlist.hpp"
#include <iostream>

using namespace std;

struct List
{
    element *head;
    element *tail;
    size_t lenght;
};

List* createList()
{
    List *l = new (nothrow) List;
    if (!l){
        return nullptr;
    }
    l->head = new element;
    l->head->next = nullptr;
    l->tail = l->head;
    l->lenght = 0;
    return l;
}

void pushFront(List *l, Data d)
{
    l->head = new element {d, l->head};
    l->lenght++;
}

Data popFront(List *l)
{
    if (l->lenght == 0){
        cout << "Nothing to delete!" << endl;
        return 0;
    }
    l->lenght--;
    element *tmp = l->head->next;
    Data val = l->head->data;
    delete l->head;
    l->head = tmp;
    return val;
}

void pushBack (List *l, Data d)
{
    element *tmp = new (nothrow) element;
    tmp->next = nullptr;
    l->lenght++;
    tmp->data = 0;
    l->tail->data = d;
    l->tail->next = tmp;
    l->tail = tmp;
}

Data popBack(List *l)
{
    if (l->lenght == 0){
        cout << "Nothing to delete!" << endl;
        return 0;
    }
    l->lenght--;
    for (element *tmp = l->head; tmp != l->tail; tmp = tmp->next){
        if (tmp->next->next ==l->tail){
            Data val = tmp->next->data;
            element *tmpDel = tmp->next;
            tmpDel = nullptr;
            delete tmpDel;
            tmp->next = l->tail;
            return val;
        }
    }
}

void deleteAfter(List *l, Data d)
{
    ;
}


void print(List *l)
{
    for (element *tmp = l->head; tmp != l->tail; tmp = tmp->next){
        cout << tmp->data << endl;
    }
}

void findChange(List *l, Data d, Data newD)
{
    for (element *tmp = l->head; tmp != l->tail; tmp = tmp->next){
        if (tmp->data == d){
            tmp->data = newD;
            break;
        }
    }
}

Data getSize(List *l)
{
    return l->lenght;
}
