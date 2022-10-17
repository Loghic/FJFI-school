#include <iostream>
using namespace std;


void rotate_array(int A[], int lenght);
void print(int A[], int length);
int factorial(int n);
double e(double eps);

int main()
{
    cout << factorial(5) << endl;
    int A[]{1,2,3,4,5,6,7,8,9};
    int lenght = sizeof(A)/sizeof(A[0]); // sizeof(A)/sizeof(int)
    rotate_array(A,lenght);
    print(A,lenght);
    cout << e(1e-5) << endl;
    return 0;
}

void rotate_array(int A[], int lenght)
{
    for (int i = 0, j = lenght - 1; i < j; j--, i++){
        // int c = A[i];
        // A[i] = A[j];
        // A[j] = c;
        swap(A[i],A[j]);

    }
}

void print(int A[], int length)
{
    for (int i {0}; i < length; i++){
        cout << "[" << A[i] << "]";
    }
    cout << endl;
}

int factorial(int n)
{
    int ans = 1;
    for (int i = 2; i <= n; i ++){
        ans *= i;
    }
    return ans;
}

double e(double eps)
{
    double soucet = 2;
    int i = 1;
    double scitanec = 1;
    do{
        i++;
        scitanec /= i;
        soucet += scitanec;
    }while(scitanec > eps);
    return soucet;
}
