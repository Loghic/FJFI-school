#include <iostream>

using namespace std;

class Numero
{
    int value;
public:
    explicit Numero(int n) :value(n) {} // possible to write explicit, so we can't get pass n1 = n2 + 10
    int summary() {return value;}

    // unary operator + as method
    Numero operator+();
    // friendly function, so we can use private instance "value"
    friend Numero operator-(Numero n);

    // binary operator +
    Numero operator+(Numero n);
    // binary operator for Numero and int
    Numero operator+(int n);
    friend Numero operator+(int n, Numero n1);
    friend Numero operator-(Numero n1, Numero n2);

    Numero& operator++();
    Numero operator++(int); // int as parameter is useless there, it has to be for postfix

    // declared outside class
    friend Numero &operator--(Numero &n);
    friend Numero operator--(Numero &n, int);
};

// Should be written like this
Numero Numero::operator+()
{
    return *this;
}

// It should be written as above

//Numero operator-(Numero n)
//{
//    return Numero{-n.summary()};
//}

// uses declaration friendly
Numero operator-(Numero n)
{
    return Numero(-n.value);
}

// Binary operator plus
Numero Numero::operator+(Numero n)
// can be declared as n1 + n2 or n1.operator+(n2), the second one is not used
{
    return Numero(value + n.value);
}

// binary operator + as method with int
Numero Numero::operator+(int n)
{
    return Numero(value + n);
}

// binary operator + as function
Numero operator+(int n, Numero n1)
{
    return Numero(n + n1.value);
}

Numero operator-(Numero n1, Numero n2)
{
    return Numero(n1.value - n2.value);
}

// has to return reference because if it didnt it wouldnt work for ++++n1
Numero& Numero::operator++()
{
    value++;
    return *this;
}

//Doesnt work how we are used to
//Numero Numero::operator++(int)
//{
//    value++;
//    return *this;
//}

Numero Numero::operator++(int)
{
    Numero result = *this;
    ++value;
    return *this;
}

// has to be passed as referenced it order to be changed
Numero &operator--(Numero &n)
{
    n.value--;
    return n;
}

// int in parameter to say the operator is postfix
Numero operator--(Numero &n, int)
{
    Numero res = n;
    n.value--;
    return res;
}

int main()
{
    Numero n1{5}, n2{0}, n3{-6};

    //    n2 = +n3;
    // same as the one above
//    n2 = n3.operator+(); // also possible but it's not used. Everything can be written as this
    // except for new and delete

//    n2 = -n3; // n2 = operator-(n3); same as the before but its not used
//
//    n2 = n1 + n3;

    // this does encapsulate int 10, even there isn't explicit written in constructor
//    n3 = n1 + 10; // this works even if it shouldn't; Because of that we can write explicit in constructor

    // Uses binary operator for operator+(int n)
//    n3 = n1 + 10;


//    n3 = 10 + n1; //Doesn't work both ways // Works thanks to the function that is friend of the class

//    n3 = n2 - n1;
//
//    n3 = n2 - 10;

    ++++n3;
    cout << n3.summary() << endl;
    n2++;
    //this doesnt work until the fucntion is changed
    n3 = n2++;
    cout << n2.summary() << endl;
    cout << n3.summary() << endl;

    --n1;
    cout << n1.summary() << endl;
    n2 = ----n1;
    cout << n2.summary() << endl;

}


/*
 * operators that cant be overloaded
 * 1. group
 * sizeof typeif . .* :: const_cast ?: and some others that resolve in compile time
 * 2. group - can be overloaded only as methods of object type
 * (type) -> () [] =
 * 3. group - can be overloaded for whole program, even libraries that are included !MIGHT BE PROBLEMATIC!
 * new delete
 * 4. group
 * other - as methods or free functions
 * 5. group - ""identificator (user declared "types")
 * 121t etc.
 */