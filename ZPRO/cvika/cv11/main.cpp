#include <iostream>
#include "linkedlist.hpp"

using namespace std;

int main()
{
    List *l;
    l = createList();
    pushFront(l, 5);
    pushFront(l, 2);
    pushFront(l, 3);
    pushFront(l, 4);
    findChange(l,3,10);
    pushFront(l, 44);
    pushBack(l, 50);
    cout << "Popped element is: " << popFront(l) << endl;
    cout << "Popped element is: " << popBack(l) << endl;
    cout << "Size is: " << getSize(l) << endl;
    pushBack(l, 21);
    pushBack(l,22);
    cout << "Popped element is: " << popBack(l) << endl;
    cout << "Size is: " << getSize(l) << endl;
    print(l);
    return 0;
}