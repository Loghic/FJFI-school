#include <iostream>

#include "concepts"

#include "type_traits"

using namespace std;

// Usage of this forbids calling with type double or X
//template<typename T> //requires integral<T>
//template<integral T> // also possible to write like this
template<integral T> requires is_integral_v<T> // also possible to use with type_traits
T Max(T a, T b) requires integral<T> // its possible to be written after fun
{
    return a > b ? a : b;
}

//SFINAE - substitution failure is not an error

const char* Max(const char* t1, const char* t2)
{
    // compares only the first character
    return *t1 < *t2 ? t1 : t2;
}

class X{};


int main() {
    int a = 5, b = 11, c;
    double d = 8.1, e = 9.2, f;
    cout << Max(a,b) << endl;
    cout << Max(d,e) << endl;

    cout << Max(double(a),d) << endl; // (double)a same as double(a)
    cout << Max<double>(a,e) << endl;

    auto text1 = "Nazdar";
    auto text2 = "Ahoj";

    cout << Max(text1, text2) << endl;

    X xa, xb;
    X xc = Max(xa, xb);

    return 0;
}
