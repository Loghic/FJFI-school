#include <iostream>
#include "Go.h"
#include <list>
#include <typeinfo>

using namespace std;

void menu(){
    cout << "What kind of graphical object do you wish to paint?\n";
    cout << "(1) Point\n";
    cout << "(2) Line segment\n";
    cout << "(3) Circle\n";
    cout << "(E) Nothing, end drawing\n\n";
    cout << "Your choice: ";
}

void drawPicture(list<Go*> picture){
    Go *ptr;
    for (std::list<Go*>::iterator it=picture.begin(); it != picture.end(); ++it){
        ptr = *it;
//        cout << typeid(*ptr).name() << endl;
        if(typeid(*ptr) == typeid(LineSegment)){
            cout << "Yay, it is a line segment! Length is: ";
            LineSegment *ptrLS = static_cast<LineSegment*>(ptr);
            cout << ptrLS->length() << endl;
        }else if(typeid(*ptr) == typeid(Circle)){
            cout << "Yay, it is a circle! The area is: ";
            Circle *ptrC = static_cast<Circle*>(ptr);
            cout << ptrC->area() << endl;
        }
        ptr->draw();
    }
}


void clearMemory(list<Go*> picture){
    Go *ptr;
    for (std::list<Go*>::iterator it=picture.begin(); it != picture.end(); ++it){
        ptr = *it;
        delete ptr;
    }
}

int main()
{
    //Go g(0); //we CAN NOT create objects of abstract class
    Go *ptr;
    list<Go*> objects;
    int c, ax, ay, bx, by,r;
    char choice;
    do{
        menu();
        cin >> choice;
        if(choice == 'E'){
            break;
        }
        cout << "Please enter color: ";
        cin >> c;
        switch (choice)
        {
            case '1':
                cout << "Enter coordinates of point: ";
                cin >> ax >> ay;
                ptr = new Point(ax, ay, c);
                break;
            case '2':
                cout << "Enter coordinates of start point: ";
                cin >> ax >> ay;
                cout << "Enter coordinates of end point: ";
                cin >> bx >> by;
                ptr = new LineSegment(ax, ay, bx, by, c);
                break;
            default:
                cout << "Enter coordinates of the centre of the circle: ";
                cin >> ax >> ay;
                cout << "Enter radius: ";
                cin >> r;
                ptr = new Circle(ax, ay, r, c);
        }
        objects.push_back(ptr);
    } while(true);
    drawPicture(objects);
    clearMemory(objects);
    return 0;
}
