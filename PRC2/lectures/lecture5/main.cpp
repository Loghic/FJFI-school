#include "trida.h"

int main() {
    prepravka<int> p(10);
    p.vypis();
    cout << endl;
    prepravka<int*> q(new int{7});
    q.vypis();
    cout << endl;
    prepravka<char*> r(new char{'c'});
    r.vypis();
    cout << endl;
    prepravka<void> s;
    s.vypis();
    cout << endl;

    return 0;
}
