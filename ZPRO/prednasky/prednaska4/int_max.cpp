#include <iostream>
#include <math.h>
#include <limits.h>
using namespace std;

int f(int i)
{
    cout << i << endl;
    return i + 1;
}


int main(void)
{
    int i = INT_MIN;
    //cout << abs(i) << endl;
    unsigned u = UINT_MAX;
    cout << u << " " << ++u << endl;
    (void)f(i);
    return 0;
}