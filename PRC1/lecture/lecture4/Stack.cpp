#include "Stack.h"

struct Stack{
    int sp; //stack pointer
    int size;
    Data *array; // useful data
};


void create(Stack *&s, int capacity)
{
    s = new Stack;
    s->sp = -1;
    s->size = capacity;
    s->array = new Data[s->size];
}

void destroy(Stack *&s)
{
    delete [] s->array;
    s->array = nullptr;
    delete s;
    s = nullptr;
}

void push(Stack *s, Data data)
{
//    if(!full(s)){
//        s->sp++;
////        s->array[s->sp] = data;
//    }else{
//        // throw exception
//        s->size *= 2;
//        Data * tmp = new Data[s->size];
//        for (int i = 0; i < s->size/2; i++){
//            tmp[i] = s->array[i];
//        }
//        delete [] s->array;
//        s->array = tmp;
//    }
    if(full(s)){
        s->size *= 2;
        Data * tmp = new Data[s->size];
        for (int i = 0; i < s->size/2; i++){
            tmp[i] = s->array[i];
        }
        delete [] s->array;
        s->array = tmp;
    }

    s->sp++;
    s->array[s->sp] = data;
//    s->array[++s->sp]
}

void pop(Stack *s)
{
    if(!empty(s)){
        s->sp--;
    }else{
        //throw exception
    }
}

Data top(Stack *s)
{
    if(!empty(s)){
        return s->array[s->sp];
    }else{
        ;//throw exception
    }
}

bool empty(Stack *s)
{
    return s->sp == -1;
}

bool full(Stack *s)
{
    return s->size-1 == s->sp;
}