#include <iostream>

using namespace std;

class Point
{
private:
    int x, y;
    double z;
public:
    Point ();
    Point (int _x, int _y, double _z) : x(_x), y(_y), z(_z) {cout << "consts with param\n";}
    void setX(int _x) {x = _x;}
    void setY(int _y) {y = _y;}
    void setZ(double _z) {z = _z;}
    int getX() {return x;}
    int getY() {return y;}
    double getZ() {return z;}
    void movePoint(int newX, int newY)
    {
        x += newX;
        y += newY;
    }
    
    void move(int newX, int newY, double newZ);
};

Point::Point()
: x(0), y(0), z(0)
{
    cout << "constructor without parameters!\n";
}

void Point::move(int newX, int newY, double newZ)
{
    x += newX;
    y += newY;
    z += newZ;
}

int main(int argc, const char * argv[]) {
    
    Point b;
    Point a(2,3,5.5);
    cout << a.getX() << " " << a.getY() << " " << a.getZ() << endl;
    
    a.movePoint(30,800);
    cout << a.getX() << " " << a.getY() << " " << a.getZ() << endl;
    
    a.move(-1000, -1000, 83.2);
    cout << a.getX() << " " << a.getY() << " " << a.getZ() << endl;
    return 0;
}
