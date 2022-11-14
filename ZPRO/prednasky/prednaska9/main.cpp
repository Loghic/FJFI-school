#include <iostream>


using namespace std;

int factorial(int n)
{
    return n + 1;
}

auto factorial(int n)->int;

auto my_max(int a, int b)
{
    return a > b ? a : b;
}

// auto my_min(auto a, auto b)
// {
//     // decltype(a) x = a;
//     return a > b ? a : b;
// }

constexpr int power(int x)
{
    return x * x;
}

template<typename T1, typename T2>
auto my_minimum (T1 a, T2 b)
{
    T1 x = a;
    return a < b ? a : b;
}

void print(int a = 2, int b = 4, int c = 5)
{
    cout << a << endl << b << endl << c << endl;
}

int main()
{
    const int N = 4;
    int A[power(N)]{0};
    print(2,3,4);
    cout << endl;
    print(4,3);
    // auto x = my_max(9,44);
    // cout << x << endl;
    // auto y = my_min(4.5, 8.7);
    // auto z = my_min(0L, 5L);
    // cout << x << endl;
    // cout << y << endl;
    // cout << z << endl;

    return 0;
}