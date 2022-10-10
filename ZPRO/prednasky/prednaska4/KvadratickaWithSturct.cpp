#include <iostream>
#include <math.h>

using namespace std;

enum struct Druh{Realne, Komplexni};
enum {a , b , c , x1=0 , x2};

struct Vysledek
{
    Druh druh;
    double vysledek[2]{};

};

Vysledek ResKvadratickouRovnici(double koef[])
{
    double d = koef[b] * koef[b] - 4 * koef[a] * koef[c];
    Vysledek vysledek;
    if (d >= 0){
        d = sqrt(d);
        vysledek.druh=Druh::Realne;
        vysledek.vysledek[x1] = (-koef[b] + d)/ 2 / koef [a];
        vysledek.vysledek[x2] = (-koef[b] - d)/ 2 / koef [a];
    }else{
        d = sqrt(-d);
        vysledek.druh=Druh::Komplexni;
        vysledek.vysledek[x1] = (-koef[b] + d)/ 2 / koef [a];
        vysledek.vysledek[x2] = (-koef[b] - d)/ 2 / koef [a];
    }
    return vysledek;
}

int main()
{
    double A[]{1,1,1};
    Vysledek vysledek = ResKvadratickouRovnici(A);
    if (vysledek.druh == Druh::Realne){
        cout << "x1: " << vysledek.vysledek[x1] << " x2: " << vysledek.vysledek[x2] << endl;
    }else{
        cout << "x1: " << vysledek.vysledek[x1] << "i x2: "<< vysledek.vysledek[x2] << "i" << endl;
    }
    return 0;
}
