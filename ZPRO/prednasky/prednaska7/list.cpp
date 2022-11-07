#include "list.hpp"
#include <iostream>

using namespace std;

void make(list& l)
{
    l.head = l.sentinel = new element{ myNULL, nullptr};
    l.length = 0;
}

void push_front(list& l, T what)
{
    l.head = new element{what, l.head};
    l.length++;
}

void push_back(list& l, T what)
{
    l.sentinel->data = what;
    l.sentinel->next = new element {what, nullptr};
    l.sentinel = l.sentinel->next;
    l.length++;
}

void push_behind(list& l, T what, element* whichOne)
{
    whichOne->next = new element{what, whichOne->next};
    // whichOne->next = myNew;
}

void pop_first(list& l)
{
    auto tmp = l.head;
    l.head = l.head->next;
    delete tmp;
    l.length--;
}

bool is_Empty(list& l)
{
    return (l.length > 0 ? false : true);
}

size_t len_list(list& l)
{
    return l.length;
}

void empty(list& l)
{
    while(!is_Empty(l)){
        pop_first(l);
    }
}

void delete_list(list& l)
{
    empty(l);
    delete l.head;
}

element* find(list& l, T what)
{
    l.sentinel->data = what;
    element* tmp = l.head;
    while(tmp->data != what){
        tmp = tmp->next;
    }

    if (tmp == l.sentinel){
        return nullptr;
    }else{
        return tmp;
    }
}

void my_print(list& l)
{
    for (element* tmp = l.head; tmp != l.sentinel; tmp = tmp->next){
        cout << tmp->data << ", ";
    }cout << endl;
}

void delete_behind(list& l, element* which)
{
    auto tmp = which->next;
    which->next = tmp->next;
    delete tmp;
}

void my_delete(list& l, element* which)
{
    if (which->next == l.sentinel){ // if deleted element is last
        l.sentinel = which;
        delete which->next;
        which->next = nullptr;
    }else{
        which->data = which->next->data;
        delete_behind(l, which);
    }
}

element* find_the_lowest(list& l)
{
    element* lowest = l.head;
    element* tmp = l.head;
    while (tmp != l.sentinel){
        if (tmp->data < lowest->data){
            lowest = tmp;
        }
        tmp = tmp->next;
    }
    return lowest;
}
