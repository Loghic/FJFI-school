#include <iostream>

using namespace std;

void test()
{
    int t[256];
    static int counter = 0;
    cout << counter++ << "\n";
    test();
}

int main() {
    cout << sizeof(int) << endl;
    test();
    return 0;
}
