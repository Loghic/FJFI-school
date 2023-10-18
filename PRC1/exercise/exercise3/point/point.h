#ifndef POINT_POINT_H
#define POINT_POINT_H

class Point{
    double x, y;
public:
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
    double distance(Point &other);

};

void print(Point &p);


#endif //POINT_POINT_H
