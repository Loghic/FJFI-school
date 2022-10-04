#include <iostream>
#include "func.hpp"
#include "func.cpp"
// playing with arrays
using namespace std;

int main()
{
    double x[] = {1.4, 3, 2, 5, 52, 13};
    int lenght = sizeof(x)/sizeof(x[0]);
    arraymax(x, lenght);
    arrayadd(x, lenght);
    arrayswap(x, lenght);
    arraymax(x, lenght);
    return 0;
}

