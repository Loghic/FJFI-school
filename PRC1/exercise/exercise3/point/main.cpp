#include <iostream>
#include "point.h"

enum {OK};

using namespace std;


int main() {
    Point a;
    a.setX(6);
    a.setY(8);
    Point b;
    b.setX(0);
    b.setY(0);
    cout << "Print 1: ";
    print(a);
    cout << "Print 2: ";
    a.print();
    cout << "Distance between point a and be is: " << a.distance(b) << endl;
    return OK;
}
