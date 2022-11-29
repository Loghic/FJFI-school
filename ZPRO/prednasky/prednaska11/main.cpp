#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

#define napis cout << "Nazdar" << endl;
#define mocnina(x) (x)*(x)
#define PRINT(x) cout << #x << " = " << x << endl;
#define my_date_(typ) struct datum {typ day, month, year;}

#define N 6
// #include "funkce.h"

#if N > 5 && N < 10
void debugging()
{
    cout << "Debugging" << endl;
}
#elif N > 10
void debugging(){}
#else
void debugging(){ cout << "Trhni si nohou" << endl;}
#endif

my_date_(int);
// my_date_(long);

int moc(int x)
{
    PRINT(x);
    return x * x;
}

void writeToFile(const char* my_name)
{
    FILE* f = fopen(my_name, "wb");
    if (!f){
        cerr << "Cannot open file: " << my_name << endl;
        exit(1);
    }
    for (int i = 0; i <= 10; i++){
        fwrite(&i, sizeof(int), 1, f);
    }
    fclose(f);
}

int main()
{
    // cout << faktorial(5) << endl;

    writeToFile("test.txt");
    napis;
    int a = 2;
    PRINT(a);
    cout << mocnina(a + 1) << endl;
    // cout << mocnina(++a) << endl;
    PRINT(a);
    PRINT(a+1)
    a = 5;
    PRINT(a+5);
    debugging();
    return 0;
}