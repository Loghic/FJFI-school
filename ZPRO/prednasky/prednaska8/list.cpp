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
    l.length++;
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

my_iterator find(list& l, T what)
{
    l.sentinel->data = what;
    element* tmp = l.head;
    while(tmp->data != what){
        tmp = tmp->next;
    }
    return my_iterator{tmp, &l};
    // if (tmp == l.sentinel){
    //     return my_iterator{tmp, &l};
    // }else{
    //     return ;
    // }
}

void my_print(list& l)
{
    // for (element* tmp = l.head; tmp != l.sentinel; tmp = tmp->next){
    //     cout << tmp->data << ", ";
    // }cout << endl;
    for(my_iterator i = begin(&l); !is_equal(i,end(&l)); go_to_next(i)){
        cout << return_value(i) << ", ";
    }
    cout << endl;
}

void delete_behind(list& l, element* which)
{
    auto tmp = which->next;
    if (tmp == l.sentinel) return;
    which->next = tmp->next;
    delete tmp;
    l.length--;
}

void my_delete(list& l, element* which)
{
    if (which->next == l.sentinel){ // if deleted element is last
        l.sentinel = which;
        delete which->next;
        which->next = nullptr;
        l.length--;
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

void sort(list& l)
{
    list tmp;
    make(tmp);
    while (!is_Empty(l)){
        element* lowest = find_the_lowest(l);
        push_back(tmp, lowest->data);
        my_delete(l, lowest);
    }
    swap(l.head, tmp.head);
    swap(l.sentinel, tmp.sentinel);
    swap(l.length, tmp.length);
    delete_list(tmp);
}

my_iterator make_iterator(list *l, element *Element)
{
    return my_iterator{Element, l};
}

bool go_to_next(my_iterator &i)
{
    if (i.acctual == i.l->sentinel){
        return false;
    }
    i.acctual = i.acctual->next;
    return true;
}

my_iterator begin(list *l)
{
    return my_iterator{l->head, l};
}

my_iterator end(list *l)
{
    return my_iterator{l->sentinel, l};
}

T return_value(my_iterator i)
{
    return i.acctual->data;
}

void set_value(my_iterator i, T value)
{
    i.acctual->data = value;
}

bool is_equal(my_iterator i1, my_iterator i2)
{
    return i1.acctual == i2.acctual;
}

