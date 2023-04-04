#include <iostream>
#include <assert.h>

using namespace std;

enum{OK};

const int N = 10;

struct Tower
{
    int h; //height
    int a[N];
};

void init(Tower & X)
{
    X.h = 0;
    for (int i = 0; i < N; i++)X.a[i] = 0;
}

void setup(Tower & X)
{
    X.h = N;
    for (int i = 0; i < N; i++)X.a[i] = N-i;
}

void step(Tower &X, Tower &Y)
{
    assert(X.h > 0);
    int d = X.a[X.h-1];
    X.h--;

    assert(Y.h < N);
    if (Y.h > 0){
        assert(Y.a[Y.h - 1] > d);
    }
    Y.h++;
    Y.a[Y.h-1] = d;
}

void printTower(Tower &X)
{
    for (int i = 0; i < N; i++){
        if (i < X.h){
            cout << X.a[i] << " ";
        }else{
            cout << "  ";
        }
    }

}

Tower A, B, C;

void print()
{
    printTower(A);
    cout << " : ";
    printTower(B);
    cout << " : ";
    printTower(C);
    cout << endl;
}

int main()
{
    // Tower A, B, C;
    setup(A);
    init(B);
    init(C);
    print();
    step(A, B);
    step(A,C);
    print();
    step(A,C);
    print();
    return OK;
}