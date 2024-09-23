#include <iostream>

using namespace std;

class Point
{
private:
    int x, y;
    double z;
public:
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

void Point::move(int newX, int newY, double newZ)
{
    x += newX;
    y += newY;
    z += newZ;
}

int main(int argc, const char * argv[]) {

    Point a;
    a.setX(10);
    a.setY(20);
    a.setZ(9.2);
    
    cout << a.getX() << " " << a.getY() << endl;
    a.movePoint(30,800);
    cout << a.getX() << " " << a.getY() << endl;
    
    a.move(-1000, -1000, 83.2);
    cout << a.getX() << " " << a.getY() << " " << a.getZ() << endl;
    return 0;
}
