#include "list.hpp"

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

void pop_first(list& l)
{
    auto tmp = l.head;
    l.head = l.head->next;
    delete tmp;
    l.length--;
}
