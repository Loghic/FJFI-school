#ifndef POINT_POINT_H
#define POINT_POINT_H

class Point{
    double x, y;
public:
    Point();
    Point(double x, double y);
    ~Point();

    double getX() const{
        return this->x;
    }

    void setX(const float x) {
        this->x = x;
    }

    double getY() const{
        return y;
    }

    void setY(const float y) {
        Point::y = y;
    }
    void print() const;
    double distance(Point &other) const;

};

void print(Point &p);
float distance(Point &p1, Point &p2);

#endif //POINT_POINT_H
