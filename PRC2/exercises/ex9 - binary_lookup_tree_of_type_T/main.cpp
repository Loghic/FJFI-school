#include <iostream>

#include "tree.h"

using namespace std;

int main() {
    // we have to specify which datatype is the structure going to be
    Tree<int> t;
    t.insert(15);
    t.insert(25);
    t.insert(10);
    t.insert(30);
    t.insert(12);
    t.insert(5);
    t.insert(11);
    t.insert(27);
    t.print();
    return 0;
}
