#include <iostream> //contains manipulators without parameters
#include "iomanip" //manipulators with params
#include "fstream"
#include "string"

using namespace std;

// class of complex numbers
class Komplex
{
    double re, im;
    friend ostream& operator<<(ostream &stream, Komplex z); // this can be anywhere in private or in public
public:
    Komplex(double re, double im) : re(re), im(im){}
};

//ostream always by reference
ostream& operator<<(ostream &stream, Komplex z)
{
    int width = stream.width();
    stream << setw(0);

    return stream << "(" << setw(width) << z.re << ", " << setw(width) << z.im << ")";

    // without setw()
//    return stream << "(" << z.re << ", " << z.im << ")";
}


istream &operator>>(istream& stream, Komplex z)
{
    //TODO
    return stream;
}

// own (Vlastni) manipulator for output of 10 spaces
ostream& spaces(ostream& stream)
{
    return stream << "          "; //10 spaces
}

// manipulator for output in binary

// binarka = binary
struct Binarka
{
    string result;
    Binarka(unsigned value)
    {
        if (value == 0){
            result = "0";
            return;
        }

        while (value){
            result += char(value%2 + '0');
            value /= 2;
        }

        std::reverse(result.begin(), result.end()); // better implementation in stack
    }
};
//dvojkova = binary
Binarka dvojkova(unsigned n)
{
    return n; // conversing constructor
}

ostream& operator<<(ostream& stream, Binarka b)
{
    return stream << b.result;
}


int main() {
//    Komplex a(3.14,5.6);
//    cout << a << endl;
    Komplex z{3.14, 5.6};
    // setw() is for the next output only, on the other hand every other e.g. hex are until we write dec again
    cout << setw(10) << z << endl;
    cout << spaces << z << endl;
    cout << spaces << setw(10) << z << endl;

    cout << dvojkova(10) << endl;
    return 0;
}
