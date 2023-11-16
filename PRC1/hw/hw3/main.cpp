#include <iostream>
#include "list.h"


using namespace std;

int main()
{
    List l;
    for(int i = 0; i < 10; i++){
        if(i % 2 == 0)
            l.pushBack(i);
        else
            l.pushFront(i);

    }
    l.print();

    cout << "-------------\nSorted list from the lowest to the highest: " << endl;
    l.sort();
    l.print();

    return 0;
}
