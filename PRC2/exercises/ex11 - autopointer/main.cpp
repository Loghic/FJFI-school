#include <iostream>

#include "autopointer.h"

const int SIZE = 3;

struct test{
    int len = SIZE;
    int data[SIZE]{};
    test(){
        for (int i = 0; i < SIZE; i++){
            data[i] = i;
        }
    }
};

int main() {

    AutoPointer<int> p(new int(3));
    AutoPointer<int> q(new int(5));
    AutoPointer<int> r(p);
    AutoPointer<test> s(new test);
    q = p;

    cout << "Size: " << s->len << endl;
    for (int i = 0; i < SIZE; i++){
        cout << s->data[i] << endl;
    }

    AutoPointer<test> t(s);

    cout << s->len << endl;

    s->data[0] = -4;
    cout << s->data[0] << endl;
    cout << t->data[0] << endl;

    return 0;
}
