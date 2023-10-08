#include "singleLinkedList.h"

enum {OK};

int main() {
    myList l1;
    makeList(l1);

    pushFront(l1,4);
    pushFront(l1,5);

    popFirst(l1);

    pushBack(l1, 10);
    pushBack(l1, 20);

    auto p = find(l1,10);
    pushBehind(l1, 8, p.actual);
    myPrint(l1);

    p = find(l1, 10);
    deleteElement(l1, p.actual);

    p = find(l1, 4);
    deleteElement(l1, p.actual);
    myPrint(l1);

    pushFront(l1,4);
    pushFront(l1,123);
    pushFront(l1,42);
    pushFront(l1,-51);
    pushBack(l1, -66);
    myPrint(l1);

    p.actual = findLowest(l1);
    cout << p.actual->data << endl;

    sort(l1);
    myPrint(l1);

    deleteList(l1);
    cout << "-------------------" << endl;

    myList l2;
    makeList(l2);
    for(int i = 0; i < 100; i += 10)
    {
        pushFront(l2, i);
    }
    myPrint(l2);

    p = myBegin(&l2);
    T myData = 0;
    do {
        setValue(p, myData);
        myData++;
    }
    while(go_to_next(p));

    myPrint(l2);

    deleteList(l2);


    return OK;
}
