#include <iostream>
#include "linkedList.hpp"

#include <iostream>

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

using namespace std;