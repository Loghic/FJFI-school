#include <iostream>
#include "list.cpp"

using namespace std;

int main()
{
    list l1;
    make(l1);
    push_front(l1,4);
    push_front(l1,5);
    pop_first(l1);
    push_back(l1, 10);
    push_back(l1, 20);

    return 0;
}