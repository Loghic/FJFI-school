#include "Pixel.h"

using namespace std;

Pixel::Pixel(unsigned int x0, unsigned int y0)
    : x(x0), y(y0)
{
    cout << "Consts with param\n";
}

Pixel::Pixel()
    : x(0), y(0)
{
    cout << "Consts without param\n";
}

ostream& operator<<(ostream &os, Pixel &p)
{
    os << "[" <<p.getX() << ", " << p.getY() << "]";
    return os; // is returning changed "output stream" (can be changed again)
}

istream& operator>>(istream &is, Pixel &p)
{
    unsigned int x,y;
    is >> x >> y;
    p.setX(x);
    p.setY(y);
    return is;
}
