#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
//    Matrix m(0,5); if T is defined and N is defined
//    Matrix<int, 4> m(0,5); // If T and N is undefined
//    Matrix<int, 4> n(0,3), o;
//    o = m + n;
//    cout << m << endl;
//    cout << o << endl;


    Matrix<int, 4> m(1,1), n(1,1), o;
    Matrix<int, 3> a(2);
    cout << a << endl;
    cout << m << endl;
    cout << n << endl;
    o = m * n;
    cout << o;
    return 0;
}
