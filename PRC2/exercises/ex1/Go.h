#ifndef EX1_GO_H
#define EX1_GO_H

//Common parent of all graphical objects
//abstract class
class Go
{
protected:
    int color;
public:
    Go(int col);
    virtual ~Go(){}
    void setColor(int col){
        color = col;
    }
    int getColor() const{
        return color;
    }
    //pure virtual method
    virtual void draw() const = 0;
};

class Point : public  Go{
protected:
    int x, y;
public:
    Point(int x, int y, int c);
    virtual ~Point(){}
    int getX() const {return x;}
    int getY() const {return y;}
    void setX(int val){x = val;}
    void setY(int val){y = val;}
    virtual void draw() const;
    friend class LineSegment;
};

//inheritance, relation IS A
class LineSegment : public Go{
protected:
    Point a, b; //composition, relation HAS A
public:
    LineSegment(int ax0, int ay0,
                int bx0, int by0,
                int c);
    //LineSegment(Point a0, Point b,
    //            int c);
    virtual ~LineSegment(){}
    Point getA() const{return a;}
    Point getB() const{return b;}
    void setA(Point p){a = p;}
    void setB(Point p){b = p;}
    void draw() const;
    float length() const;
};

class Circle : public Go{
protected:
    Point centre;
    unsigned int radius;
public:
    Circle(int cx, int cy, unsigned int r, int c);
    virtual ~Circle(){}
    Point getCentre() const{return centre;}
    unsigned int getR() const{return radius;}
    void setCentre(Point p){centre = p;}
    void setR (int r){radius = r;}
    virtual void draw() const;
    float area() const;
};

#endif //EX1_GO_H
