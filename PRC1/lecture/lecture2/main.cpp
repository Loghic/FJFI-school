#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

enum {OK, ERROR = 100};


const char* help = R"(SORT - program for sorting files
USE: SORT [parameter] < [input file] > [output file]
Possible parameters:
-n or /n sorts numbers using the first number on line
-l or /l lexicographical sorting
Ferda Mravenec, prace vseho druhu)";

void print_help()
{
    cerr << help << endl;
    exit(ERROR);
}

// Trying main with parameters
int main(int argc, char* argv[])
{
    print_help();
    cout << "ahoj" << endl;
    return OK;
}

//    Used in main during lecture
//    bool b = false;
//    bool c = true;
//    cout << boolalpha << b << " " << noboolalpha << c << endl;
//    char d = 'a';
//    cout << (int)d << endl;
//    double delta = .1;
//    double x = 0;
//    int g = 10'000'000;
//    cout << g << endl;
//    while(x < 1.0){
//        x+=delta;
//        cout << x << endl;
//        if (x > 100){
//            cerr << "Wtf is going on!";
//            return ERROR;
//        }
//    }
//
//    int y = 5e29;
//    double z = 5e-3;
//    cout << y << " " << z << endl;
