#include "Go.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

Go::Go(int col) :
        color(col)
{
    cout << "Go ctor\n";
}

/*
void Go::draw() const{
    cout << "Go with color "
         << color << endl;
}
*/

Point::Point(int x0, int y0, int c)
        : Go(c), x(x0), y(y0)
{
    cout << "Point ctor\n";
}

void Point::draw() const{
    cout << "Point [" << x << ", " << y << "] with color "
         << color << endl;
}

LineSegment::LineSegment(int ax0, int ay0,
                         int bx0, int by0, int col)
        : Go(col), a(ax0, ay0, col), b(bx0, by0, col)
{
    cout << "LineSegment ctor\n";
}

void LineSegment::draw() const{
    cout << "Line segment from point ";
    a.draw();
    cout << "to point: ";
    b.draw();
}

float LineSegment::length() const{
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return sqrt(dx*dx + dy*dy);

}

Circle::Circle(int cx, int cy, unsigned int r, int col)
    : Go(col), centre(cx,cy, col), radius(r)
{
    cout << "Circle ctor\n";
}

void Circle::draw() const{
    cout << "Circle with centre at point ";
    centre.draw();
    cout << "With radius: ";
    cout << "Radius " << radius << endl;
}

float Circle::area() const
{
    return M_PI * radius * radius;
}

