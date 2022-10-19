#include <iostream>
#include <math.h>

using namespace std;

enum DruhReseni { Realne, Komplexni };

enum {a, b, c};// indexes
enum {x1, x2}; //indexes

DruhReseni ResKvadratickouRovnici(double const koef[], double vysledek[])
{
    double d = koef[b] * koef[b] - 4 * koef[a] * koef[c]; // d is discriminant
    if (d >= 0){
        d = sqrt(d);
        vysledek[x1] = (-koef[b] + d)/(2 * koef[a]);
        vysledek[x2] = (-koef[b] - d)/(2 * koef[a]);
        return Realne;
    }else{
        d = sqrt(-d);
        vysledek[x1] = -koef[b]/ 2 * koef [a];
        vysledek[x2] = d / 2 * koef [a];
        return Komplexni;
    }

}



int main()
{
    double A[] = {1,1,1};
    double vysledek[2] {};
    int druh = ResKvadratickouRovnici(A, vysledek);
    if (druh == Realne){
        cout << "x1: " << vysledek[x1] << " x2: " << vysledek[x2] << endl;
    }else{
        cout << "x1: " << vysledek[x1] << " x2: +-" << vysledek[x2] << "i" << endl;
    }
    return 0;
}
