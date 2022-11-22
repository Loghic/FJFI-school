#include <iostream>
#include "list.hpp"

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
    // auto p = find(l1,10);
    // push_behind(l1, 8, p);
    // my_print(l1);
    // p = find(l1, 10);
    // // dellete p; // !!!!!!!
    // my_delete(l1, p);
    // p = find(l1, 4);
    // my_delete(l1, p);
    // my_print(l1);
    // push_front(l1,4);
    // push_front(l1,123);
    // push_front(l1,42);
    // push_front(l1,-51);
    // push_back(l1, -66);
    // my_print(l1);
    // p = find_the_lowest(l1);
    // cout << p->data << endl;
    // sort(l1);
    my_print(l1);

    
    delete_list(l1);

    return 0;
}