#include <iostream>

#include "seznam.h"

using namespace std;

using sezint = Seznam<int>;

template<class T>
using sp = Seznam<T*>;

template<class T>
constexpr T pi = 3.14159265358979;


int main()
{
    double x = pi<int>;
    double y = pi<double>;
    double z = pi<float>;
    cout << z << endl;
//    Element<int> x{1, nullptr};
//    cout << x.data << endl;
    Element<int> *e = new Element<int>(1, nullptr);
    cout << e->counter << endl;
    Seznam<int> s;
    s.pushFront(5);
    s.pushFront(10);
    s.pushFront(15);
    *e = s.getHead();
    cout << e->counter << endl;

    s.print();
    return 0;
}
