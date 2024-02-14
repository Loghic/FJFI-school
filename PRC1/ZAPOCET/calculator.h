#ifndef ZAPOCET_CALCULATOR_H
#define ZAPOCET_CALCULATOR_H
#include "string"

using namespace std;


class calculator {
protected:
    string num1;
    string num2;
    int mul;
public:
    calculator(string n1, string n2);

    void setNum1(string NewNum) {num1 = NewNum;}
    string getNum1() const{return num1;}
    void setNum2(string NewNum) {num2 = NewNum;}
    string getNum2() const{return num2;}
    void setMultiplier(int newMul) {mul = newMul;}
    int getMultiplier() const{return mul;}

    string addition();
    string subtraction();
    string multiplication();
    string divison();
    string power();
};


#endif
