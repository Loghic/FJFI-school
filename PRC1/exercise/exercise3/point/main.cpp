#include <iostream>
#include "point.h"

enum {OK};

using namespace std;


int main() {
    Point a(6,8);
    Point b;
    Point *pc;
    pc = new Point(9,9);

    cout << "Print 1: ";
    print(a);
    cout << "Print 2: ";
    a.print();
    Point c {3,4};
    cout << "Distance between point a and b is: " << a.distance(b) << endl;
    delete pc;
    pc = nullptr;
    cout << "Distance between point b and c is: " << b.distance(c) << endl;
    cout << "Distance between point a and c is: " << a.distance(c) << endl;
    cout << "|ac| = " << distance(a,c) << endl;
    return OK;
}
