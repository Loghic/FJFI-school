#include <iostream>

enum {OK,ERROR = 100};
using namespace std;

int main() {
    bool b = false;
    bool c = true;
    cout << boolalpha << b << " " << noboolalpha << c << endl;
    char d = 'á';
    cout << (int)d << endl;
    return OK;
}
