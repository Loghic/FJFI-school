#include <iostream>
#include "stack.hpp"

using namespace std;

enum {OK, ERROR_WRONG_INPUT = 100, ERROR_DIDNT_ALLOCATE};

int main()
{
    Stack *st;
    int N;
    cout << "Please eneter capacity of stack: ";
    cin >> N;
    if (N < 0){
        cout << "Wrong input!" << endl;
        return ERROR_WRONG_INPUT;
    }

    st = createStack(N); // allocate memory

    if (!st){
        cerr << "Creation of stack failed\n";
        return ERROR_DIDNT_ALLOCATE;
    }

    int i = 0;
    while (!isFull(st)){
        push(st, i);
        i++;
    }

    while (!isEmpty(st)){
        cout << top(st) << endl;
        pop(st);
    }
    
    // for (int i = 0; i < N; i++){
    //     push(st, i);
    // }

    // for (int i = 0; i < N; i++){
    //     cout << top(st) << endl;
    //     pop(st);
    // }

    destroyStack(st); // free memory

    // push(st, 5); // program error dereferencing nullptr (it this is after destroyStack)

    return OK;
}