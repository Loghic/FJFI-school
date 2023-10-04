#include <iostream>

using namespace std;


/*
 Implementation of function swap
 */

enum {OK};

//passed by referenced
void swapPtr(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

//passed by pointer
//void swap(int* pa, int* pb)
{
 int c = *pa;
 *pa = *pb;
 *pb = c;
}

int main() {
    int x = 1, y =2;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swap(&x,&y);
    cout << "After swap x = " << x << ", y = " << y << endl;
    return OK;
}
