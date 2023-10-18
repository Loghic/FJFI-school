#include "point.h"
#include <iostream>
#include <cstdlib>

Point::Point()
{
    std::cout << "Constructor without parameters\n";
    setX(0);
    setY(0);
}

Point::Point(double x, double y)
    : x(x), y(y)
{
    std::cout << "Constructor with two parameters\n";
}

Point::~Point()
{
    std::cout << "Destructor!\n";
}

double Point::distance(Point &other) const
{
    return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y,2));
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

float distance(Point &p1, Point &p2)
{
    return p1.distance(p2);
}