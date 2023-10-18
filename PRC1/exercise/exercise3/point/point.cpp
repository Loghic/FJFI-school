#include "point.h"
#include <iostream>
#include <cstdlib>

double Point::distance(Point &other)
{
    return sqrt(pow(this->x + other.x, 2) + pow(this->y + other.y,2));
}

void Point::print() const
{
    std::cout << "[" << this->getX() << ", " << getY() << "]\n";
}

void print(Point &p)
{
    p.print();
    // cout << "[" <<  p.getX() << ", " << p.getY() << "]" << endl;
}