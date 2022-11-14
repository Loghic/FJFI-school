#include <iostream>
#include <math.h>

using namespace std;


typedef double (*fun)(double);
using fun = double (*)(double x);

double power(double x)
{
    return x * x;
}

void table(fun f, double from, double to, int size, const char * name)
{
    if (size - 1 <= 0){
        cout << "Cannot do that sry" << endl;
        return;
    }
    double step = (to-from) / (size - 1);
    cout << "Tabulka funce " << name << endl;
    cout << "x          f(x)" << endl;
    cout << "---------------" << endl;

    for (int i = 0; i < size; i++){
        double x = from + i*step;
        cout << x << "        " << f(x) << endl;
    }


}

int main()
{
    // fun f = power; // &power
    // cout << f(2.0) << endl; // cout << (*f)(2.0) << endl;
    // table(power, 0, 1, 11, "power");
    table(sin, 0, 3.14159265358, 20, "sin");

    return 0;
}