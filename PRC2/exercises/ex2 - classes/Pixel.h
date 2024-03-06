#ifndef EX2_PIXEL_H
#define EX2_PIXEL_H

#include "iostream"

class Pixel
{
    unsigned int x,y;
public:
    Pixel(unsigned int x0, unsigned int y0);
    Pixel();
    void setX(unsigned int val) {x = val;}
    void setY(unsigned int val) {y = val;}
    unsigned int getX() const {return x;}
    unsigned int getY() const {return y;}

};

std::ostream& operator<<(std::ostream &os, Pixel &p);
std::istream& operator>>(std::istream &is, Pixel &p);

#endif //EX2_PIXEL_H
