#include "func.hpp"
#include <iostream>

using namespace std;

void arraymax(double x[], int lenght)
{
    double max = x[0];
    int imax = 0;
    
    for (size_t i {0}; i < lenght; i++)
        if (x[i] > max){
            max = x[i];
            imax = i;
        }
    cout << "Maximum is: " << max << " with idx " << imax << endl;
}

void arrayadd(double x[], int lenght)
{
    double res = 0;

    for (size_t i {0}; i < lenght; i++){
        res += x[i];
    }

    cout << "The result of element additon is: " << res << endl;
}

void arrayswap(double x[], int lenght)
{
    for (int i {0}; i < lenght; i++){
        cout << x[i] << " ";
    }
    cout << endl;
    cout << "Please choose which elements u want to swap, first position is 0: ";
    int n1, n2;
    double tmp;
    cin >> n1 >> n2;
    tmp = x[n1];
    x[n1] = x[n2];
    x[n2] = tmp;

    cout << "New array: " << endl;
    for (int j {0}; j < lenght; j++){
        cout << x[j] << "  ";
    }
    cout << endl;
}
