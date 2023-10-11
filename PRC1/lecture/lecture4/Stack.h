#ifndef LECTURE4_STACK_H
#define LECTURE4_STACK_H

using Data = int;

struct Stack; //forward declaration

void create(Stack *&s, int capacity); // creates empty stack
void destroy(Stack *&s); //destroys stack

void push(Stack *s, Data data); //pushes data on top of the stack
void pop(Stack *s); //remove data from top
Data top(Stack *s); //returns data from top

bool empty(Stack *s); // tests if the stack is empty
bool full(Stack *s); // tests if the stack is full


#endif //LECTURE4_STACK_H
