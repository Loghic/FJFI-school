#include <iostream>

using namespace std;
void sum(double[],double[],double[]);
void print(double[]);
const int N = 5;

int main()
{
    double x[N] = {1.2,1.5,23,53,3};
    double y[N] = {5.2,15,2.3,52.3,3.1};
    double z[N];
    sum (x,y,z);
    print(z);

    return 0;
}

void sum(double x[],double y[],double z[])
{
    for (int i = 0; i < N; i++){
        z[i] = x[i] + y[i];
    }
}

void print(double z[])
{
    for (int j = 0; j < N; j++){
        cout << z[j] << ", ";
    }cout << endl;
}
