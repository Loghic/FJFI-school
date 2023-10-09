#include <iostream>

using namespace std;

enum {OK};

void f()
{
    cout << "hello" << endl;
}

class watcher{
public:
    watcher()
    {
        cout << "Watch out!" << endl;
    }
};


void funkce(int n)
{
    // watcher x calls constructor and destructor after the block if ended
    if (int g; n = 42) watcher x; //g is local in if block
}

int i = 42;

void funkce2(int n)
{
    cout << i << endl;
    int i = 9;
    {
        cout << i << endl;
        cout << ::i << endl; // :: for global variable
        int i = 2;
        cout << i << endl;
    }
    cout << i << endl;
}

int main() {

//    int i;
//    i = 9.9; //its gonna be 9

// for empty commands, ways how to write them
    5; // both of them do nothing
    f; // does nothing
    ; // this too
    {
        // this does nothing
    }
    (void) 0; //does nothing
// //////////////
//    int i = 9;
//    if(i)
//    {
//        int j = 10;
//    }

    int i = 10;
    if (i){
        funkce(30);
    }

    funkce2(20);

//    int pole[5] = {}; //array full of nulls
    int pole[5] = {0,1,2,3,4};
    cout << "------------------------" << endl;
    for (int i = 0; i < 5; i++) cout << pole[i] << ", "; cout << "\n";
    for (int i = 0,  j = 4; i < j; i++, j--) swap(pole[i],pole[j]);
    cout << "------------------------" << endl;
    for (int i = 0; i < 5; i++) cout << pole[i] << ", "; cout << "\n";

    return OK;
}

// if (cond) command
// if (cond) command1 else command2

//while (cond) command;
//while (cond); // lze i takto pokud v podmince je cely cyklus
//doporucuje se
//while (cond)
//; // a strednik na dalsi radce, popr, prazdny blok

//do command while (cond); // do while

//for(init; cond; step) command;
