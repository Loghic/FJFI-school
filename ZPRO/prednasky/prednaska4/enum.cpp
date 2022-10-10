#include <iostream>

using namespace std;

enum den {Pondeli, Utery, Streda, Ctvrtek, Patek, Sobota, Nedele};
enum karta {Sedm = 7, Osm, Devet, Deset}; // "=" prirazuje hodnotu 1. prvku nebo k xx. prvku a dalsi jsou +1 ney predchozi
//enum pokus {Sedm, Pondeli}; //Nelze

enum class ZpusobOtevreni{Cteni, Zapis, CteniZapis}; //lze pouzit "struct" misto class
enum class Opravneni{Cteni, Zapis, Spusteni};

int main(void)
{
    den dnes = Pondeli;
    //dnes = Sedm; //Nelze
    cout << dnes << endl;
    cout << Sedm << endl;
    cout << Osm << endl;
    ZpusobOtevreni zo = ZpusobOtevreni::Cteni;
    cout << (int)zo << endl;
    return 0;
}