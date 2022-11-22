#include "linkedList.hpp"

using namespace std;

int main()
{
    List *l = createList();
    pushFront(l, 12);
    pushFront(l, 14);
    popFront(l);
    pushFront(l, 10);
    pushFront(l, 2);
    print(l);
    clean(l);
    pushFront(l,10);
    pushFront(l, 10);
    pushFront(l, 2);
    pushBack(l,30);
    pushBack(l,5);
    print(l);
    return 0;
}