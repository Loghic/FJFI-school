#include "GO.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

Go::Go(int c)
    : color(c)
{
    cout << "Go constructor\n";
}

Point::Point(int x0, int y0, int c)
    : Go(c), x(x0), y(y0)
{
    cout << "Point constructor\n";
}

LineSegment::LineSegment(int ax, int ay, int bx, int by, int c)
    : Go(c), a(ax, ay, c), b(bx, by, c)
{
    cout << "LineSegment constructor\n";
}

Go::~Go()
{
    cout << "Go destructor\n";
}

Point::~Point()
{
    cout << "Point destructor\n";
}

LineSegment::~LineSegment()
{
    cout << "LineSegment destructor\n";
}

/*
void Go::draw() const
{
    cout << "Go, color " << color << endl;
}
*/

void Point::draw() const
{
    cout << "Point [" << x << ", " << y
         << "], color " << color << endl;
}

void LineSegment::draw() const
{
    cout << "Line segment from ";
    a.draw();
    cout << "to ";
    b.draw();
}

double LineSegment::length() const
{
    double dx = a.x - b.x; // double dx = a.getX() - b.getX()
    double dy = a.y - b.y; // double dy = a.getY() - b.getY()
    return sqrt(dx*dx + dy*dy);
}
