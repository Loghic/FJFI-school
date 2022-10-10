#include <iostream>

using namespace std;

enum den {Pondeli, Utery, Streda, Ctvrtek, Patek, Sobota, Nedele};
enum karta {Sedm = 7, Osm, Devet, Deset}; // "=" assigns value to 1. element and next one is bigger (value + 1)
//enum test {Sedm, Pondeli}; //Not possible to use already used name

enum class ZpusobOtevreni{Cteni, Zapis, CteniZapis}; //lze pouzit "struct" misto class
enum class Opravneni{Cteni, Zapis, Spusteni};

int main(void)
{
    den dnes = Pondeli;
    //dnes = Sedm; //Not possible
    cout << dnes << endl;
    cout << Sedm << endl;
    cout << Osm << endl;
    ZpusobOtevreni zo = ZpusobOtevreni::Cteni;
    cout << (int)zo << endl;
    return 0;
}