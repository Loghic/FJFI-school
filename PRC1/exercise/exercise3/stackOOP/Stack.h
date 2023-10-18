#ifndef STACKOOP_STACK_H
#define STACKOOP_STACK_H
typedef int Data;


class Stack {
    int size;
    int sp;
    Data *array;
public:
    Stack(int capacity);
    ~Stack();
    void push(Data d);
    void pop();
    Data top() const;
    bool isEmpty() const {return (sp == -1);}
    bool isFull() const {return sp >= size-1;}
    int getSize() const {return size;}
};


#endif //STACKOOP_STACK_H
