#include <iostream>

using namespace std;

struct Datum
{
    int den;
    int mesic;
    int rok;
};

int main()
{
    Datum dnes {10, 10, 2022};//inicializace
    //dnes.den = 10;
    cout << dnes.den << " " << dnes.mesic << " " << dnes.rok << " " << endl;
    return 0;
}