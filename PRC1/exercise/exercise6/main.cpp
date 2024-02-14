#include <iostream>
#include "GO.h"
#include <list>
#include <typeinfo>

using namespace std;

enum {OK};

void drawPicture(list<Go*> objects)
{
    Go *ptr;
    for (list<Go*>::iterator it=objects.begin(); it != objects.end(); ++it) {
        ptr = *it;
//        cout << typeid(*ptr).name() << endl; // this doesnt work how it should
        if (typeid(*ptr) == typeid(LineSegment)){ // works only if ptr is not a null pointer
            cout << "yay, it is a line segment. Lenght: ";
//            ptr->length(); // this doenst work because parent cant be in place of child, but it works the other way
            LineSegment *lsp = static_cast<LineSegment*>(ptr);
            cout << lsp->length() << endl;
        }
        ptr->draw();
    }
}

void releaseObjects(list<Go*> &objects)
{
    for (list<Go*>::iterator it=objects.begin(); it != objects.end(); ++it) {
        delete *it;
    }
    objects.clear();
}

char menu()
{
    char c;
    cout << "Which type of object do you wish to draw: \n";
    cout << "(1) Point \n";
    cout << "(2) Line segment\n";
    cout << "(e) nothing ,end drawing\n\n";
    cout << "Your choice: ";
    cin >> c;
    // next could be chosen different color
    return c;
}

int main() {
//    Go g(0); // can't make variable like this


    list<Go*> objects; // list of graphic objects pointers
    Go *ptr; // but I can use it as pointer to it


    int ax, ay, bx, by, c;
    while(true) // for(;;)
    {
        char choice = menu();
        if (choice == 'e' || choice == 'E'){
            break;
        }
        cout << "Which color will you use?\n Color = ";
        cin >> c;
        switch (choice) {
            case '1':
                cout << "Please, enter coordinates of point: ";
                cin >> ax >> ay;
                ptr = new Point(ax, ay, c);
                break;
            default: //user wants to draw a line
                cout << "Please, enter start coordinates: ";
                cin >> ax >> ay;
                cout << "Please, enter end coordinates: ";
                cin >> bx >> by;
                ptr = new LineSegment(ax, ay, bx, by, c);
        }
        objects.push_back(ptr);
    }
    drawPicture(objects);
    releaseObjects(objects);


//    LineSegment ab (0,0, 3,4,42);
//    ab.draw();
//    cout << "Length: " << ab.length() << endl;
    return OK;
}
