#include <iostream>
#include <math.h>

using namespace std;

enum struct Druh{Realne, Komplexni};
enum {a1 , b1 , c1 , x1=0 , x2};

struct Vysledek
{
    Druh druh;
    double vysledek[2]{};

};

Vysledek ResKvadratickouRovnici(double koeficient[])
{
    double a = koeficient[a1];
    double b = koeficient[b1];
    double c = koeficient[c1];
    
    double d = b*b - 4*a*c;
    Vysledek vysledek;
    double pCitatel = -b + d;
    double nCitatel = -b - d;
    double jmenovatel = 2 * a;
    if (d >= 0){
        d = sqrt(d);
        vysledek.druh=Druh::Realne;
        vysledek.vysledek[x1] = pCitatel / jmenovatel;
        vysledek.vysledek[x2] = nCitatel / jmenovatel;
    }else{
        d = sqrt(-d);
        vysledek.druh=Druh::Komplexni;
        vysledek.vysledek[x1] = pCitatel / jmenovatel;
        vysledek.vysledek[x2] = nCitatel / jmenovatel;
    }
    
    return vysledek;
}

int main()
{
    double rovnice[]{1,1,1};
    Vysledek vysledek = ResKvadratickouRovnici(rovnice);
    if (vysledek.druh == Druh::Realne){
        cout << "x1: " << vysledek.vysledek[x1] << " x2: " << vysledek.vysledek[x2] << endl;
    }else{
        cout << "x1: " << vysledek.vysledek[x1] << "i x2: "<< vysledek.vysledek[x2] << "i" << endl;
    }
    return 0;
}
