#include <iostream>
#include "Stack.h"

using namespace std;

enum {OK};

int main() {
    Stack s(5);
    for (int i = 0; i < 5; i++){
        s.push(10*(i+1));
    }
    for (int i = 0; i < 5; i++){
        cout << s.top() << ", ";
        s.pop();
    }
    return OK;
}
