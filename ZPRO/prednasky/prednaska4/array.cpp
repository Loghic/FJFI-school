#include <iostream>

using namespace std;

int A[5] = {1,2,3,4,5,}; //globalni array se vynuluje, lokalni ne

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
    B[0] = 8; //nevynulovane pole
    cout << A[5] << endl; //nekontroluje mi to jestli se trefim do pameti
    int i = 0;
    while (i < 5){
        B[i] = A[i];
        i++;
    }
    return 0;
}