#include <iostream>
#include "stack.hpp"

using namespace std;

struct Stack{
    int capacity;
    int sp; // sp = stack pointer
    Data *data;
};

Stack* createStack(int size)
{
   Stack *s = new(nothrow) Stack;
   if (!s){
    return nullptr;
   }
   s->capacity = size; //(*s).capacity = size;
   s->sp = -1;
   s->data = new Data[size];
   return s;
}

void destroyStack(Stack *&s)
{
    delete [] s->data; // delete of array / list -> [] because its an array
    delete s;
    s = nullptr;
}

void push(Stack *s, int d)
{
    if (!isFull(s)){
        s->sp++;
        s->data[s->sp] = d;
    }else{
        // exception
        cout << "Stack Full" << endl;
    }
}    

void pop(Stack *s)
{
    if (!isEmpty(s)){
        // s->data[s->sp] = 0; not needed
        s->sp--;
    }else{
        //exception
        cout << "Stack is empty" << endl;
    }
}

Data top(Stack *s)
{
    return s->data[s->sp];
}

bool isEmpty(Stack *s)
{
    return (s->sp == -1);
    // if (s->sp == -1){
    //     return true;
    // }else{
    //     return false;
    // }
}

bool isFull(Stack *s)
{
    return (s->sp == s->capacity - 1);
    // if (s->sp == s->capacity){
    //     return true;
    // }else{
    //     return false;
    // }
}

int getSize(Stack *s)
{
    return s->sp;
}