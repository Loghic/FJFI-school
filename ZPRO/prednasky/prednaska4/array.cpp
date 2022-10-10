#include <iostream>

using namespace std;

int A[5] = {1,2,3,4,5,}; //every element of array is set to 0 in global array, in local there're garbage values

void f(int a)
{
    a = 9;
}

void ff (int A[])
{
    A[1] = 999;
}


int main()
{
    ff(A);
    int b = 88;
    f(b);
    A[1] = 9;
    int B[5];
    B[0] = 8; //Array with garbage value
    cout << A[5] << endl; //Doesn't check if I access memory that belongs to me
    int i = 0;
    while (i < 5){
        B[i] = A[i];
        i++;
    }
    return 0;
}