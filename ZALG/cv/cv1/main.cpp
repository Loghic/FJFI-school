#include <iostream>
using namespace std;

struct myData
{
    // constructor for newer version
    string name = "";
    int red = 0;
    int blue = 0;
    int green = 0;
    myData *next = nullptr;
    // constructor for older version
    // myData() : name (""), red (0), blue (0), green(0), next(nullptr) { } // constructor
};

myData *list;

void push( myData *p)
{
    p->next = list;
    list = p;
}

void myPrint()
{
    for (myData *tmp = list; tmp != nullptr; tmp = tmp->next){
        cout << "Name: " << tmp->name << " R: " << tmp->red;
        cout << " B: " << tmp->blue << " G: " << tmp->green;
        cout << endl;
    }
}

int x = 10;
int y = 20;

void swap (int * a, int  * b)
{
    cout << "a = " << *a << " b= " << *b << endl;
    int t = *a;
    *a = *b;
    *b = t;
    cout << "a = " << *a << " b= " << *b << endl;
}



int main()
{
    cout << "x = " << x << " y= " << y << endl;
    swap(&x,&y);
    cout << "x = " << x << " y= " << y << endl;
    myData p;
    p.blue = 0;
    p.green = 0;
    p.red = 255;
    p.name = "Red";
    push(&p);
    myData p1;
    p1.blue = 255;
    p1.green = 0;
    p1.red = 0;
    p1.name = "Blue";
    push(&p1);
    myPrint();


    cout << "Hello world!" << endl;
    return 0;
}