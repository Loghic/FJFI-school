#include <iostream>

using namespace std;

void mySwap(int &, int &);
void mySwap(int &&, int &&);

int main()
{
    int* p;
    p = new int {5};
    cout << *p << endl;
    delete p;

    int n;
    n = 8;
    p = new int[n] {1, 2, 3, 4, 5};
    for (int i = 0; i < n; i++){
        cout << p[i] << ", ";
    }
    cout << endl;
    delete[] p;

    int(*q)[5] = new int[n][5] { {1,2,3,4,5},{},{}};
    delete[] q;

    /////////////////////////////////////

    int& r = n;
    cout << "r: " << r << " n: " << n << endl;
    r = 98;
    cout << "r: " << r << " n: " << n << endl;
    p = &r;
    *p = 100;
    cout << "p: " << *p << " r: " << r << " n: " << n << endl;
    cout << "p: " << p << " r: " << &r << " n: " << &n << endl;
    
    int x = 8, y = 6;
    cout << "x: " << x << " y: " << y << endl;
    mySwap(x,y);
    cout << "x: " << x << " y: " << y << endl;

    return 0;
}

void mySwap(int & a, int & b) // mySwap(x,y);
{
    int c = a;
    a = b;
    b = c;
}

void mySwap(int &&a, int &&b) // mySwap(x+1, y+1);
{
    int c = a;
    a = b;
    b = c;
}