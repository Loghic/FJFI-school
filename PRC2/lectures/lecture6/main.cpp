#include <iostream>

using namespace std;

template<class T>
struct type2type
{
    using type = T;
};

template<int Value>
struct int2type
{
    enum {result = Value};
};

const int Value = 15;

// Choose one of the types in compile time
template<bool con, class T1, class T2>
struct if_else;

template<class T1, class T2>
struct if_else<true, T1, T2>
{
    using type = T1;
};

template<class T1, class T2>
struct if_else<false, T1, T2>
{
    using type = T2;
};

template<bool con, class T1, class T2>
using if_else_t = typename if_else<con,T1,T2>::type;

//Factorial in compile time
const int N = 5;

template<int N>
struct factorial
{
    enum{res = N*factorial<N-1>::res};
};

template<>
struct factorial<0>
{
    enum {res = 1};
};
template<int N>
constexpr int factorial_v = factorial<N>::res;

int main() {
//    type2type<int>::type x = int2type<Value>::result;
//    if_else<(Value > 10), int, double>::type x = 15;
    if_else_t<(Value > 10), int, double> x = 5;
    cout << typeid(x).name() << endl;
//    int A[factorial<5>::res];
    int A[factorial_v<4>];
    cout << factorial<6>::res << endl;
    cout << factorial_v<4> << endl;
    return 0;
}
