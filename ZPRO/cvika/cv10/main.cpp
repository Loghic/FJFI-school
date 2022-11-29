#include <iostream>
#include "cmath"

using namespace std;

double f1(double x)
{
    return tan(x) - x;
}

double f2(double x)
{
    return sin(x);
}

void decide (double a, double b, double &x, double eps)
{
    double c = (a+b)/2;
    if (abs(b-a) > eps){
        if (f1(a)*f1(c) <= 0){
            decide(a,c,x,eps);
        }else{
            decide(c,b,x,eps);
        }
    }else{
        x = c;
    }
}

void whileDecide (double (*f)(double), double a, double b, double &x, double eps)
{
    while (abs(b-a) > eps){
        x = (a+b)/2;
        if (f(a)*f(x) < 0){
            b = x;
        }else{
            a = x;
        }
    }
}


int main()
{
    double a = 7;
    double b = 8;
    double x = 0;
    double eps = 0.00001;
    decide(a,b,x,eps);
    cout << x << endl;
    x = 0;
    a = 7;
    b = 8;
    whileDecide(f1, a, b, x, eps);
    cout << x << endl;
    // int *a;
    // int *b;
    // int dim = 0;
    // cout << "Please enter positive int: ";
    // cin >> dim;
    // if (dim <= 0){
    //     cerr << "Not a possitive number of dimension\n";
    //     return 1;
    // }
    // a = new int[dim];
    // b = new int[dim];
    // for (int i {0}; i < dim; i++){
    //     a[i] = i;
    //     b[i] = dim -i;
    // }
    // int *c;
    // c = new int[dim];
    // for (int i {0}; i < dim; i++){
    //     c[i] = a[i] * b[i];
    // }
    // for (int i {0}; i < dim; i++){
    //     // cout << "a[" << i << "] = " << a[i] << ", b[" << i << "] = " << b[i] << endl;
    //     cout << c[i] << endl;
    // }

    // delete [] c;
    // delete []a;
    // delete []b;
    return 0;
}