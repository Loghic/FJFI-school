#include <iostream>
#include "Stack.h"

using namespace std;

enum {OK};

const int MAX_SIZE = 5;


int main() {
    Stack *myStack;
    create(myStack,MAX_SIZE);
    for (int i = 0; i < MAX_SIZE*2-2; i++){
        push(myStack,i+1);
    }

    push(myStack, 30);

    cout << full(myStack) << endl;

    cout << "--------------------" << endl;

    while (!empty(myStack)){
        cout << top(myStack) << endl;
        pop(myStack);
    }


    destroy(myStack);

    return OK;
}
