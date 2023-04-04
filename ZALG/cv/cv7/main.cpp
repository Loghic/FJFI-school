#include <iostream>
#include <time.h>
using namespace std;

const int N = 100;
int a[N]; // = { 3,12,5,6,20,4,54,95,7 };

void swap(int& n, int& m) {
    int t = n;
    n = m;
    m = t;
}

void heapify(int i, int k) {
    while(2*i+1<=k){
        int v = 2 * i + 1; // challenger
        if (v + 1 <= k && a[v + 1] > a[v])v++;
        if (a[i] < a[v]) {
            swap(a[i],a[v]);
            i = v;
        }
        else {
            i = k + 1; //stops while cycle
        }
    }
}

void heapsort() {
    for (int i = N - 1; i >= 0; i--) {
        heapify(i, N - 1);
    }
    for (int k = N - 1; k >= 1; k--) {
        swap(a[0], a[k]);
        heapify(0, k - 1);
    }
}

void print() {
    for (int element : a) {
        cout << element << endl;
    }
    cout << endl;
}

void init()
{
    srand (time(nullptr));
    for (int i = 0; i < N; i++)
        a[i] = rand() % 10000 + 10000 * (rand() % 10000);
}

int main()
{
    init();
    // print();
    heapsort();
    print();
    cout << "O.K." << endl;
}
