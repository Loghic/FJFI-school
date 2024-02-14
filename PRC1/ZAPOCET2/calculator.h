#ifndef ZAPOCET2_CALCULATOR_H
#define ZAPOCET2_CALCULATOR_H

#include "vector"
#include "string"


class calculator {
    std::vector<int> num1;
    std::vector<int> num2;
    bool num1Plus = true;
    bool num2Plus = true;
    int num1Len{};
    int num2Len{};
public:
    calculator();
    calculator(std::string number1, std::string number2);
    ~calculator();

    void setNumber1(std::string number);
    std::string getNumber1() const;
    int getNumber1Len() const {return num1Len;}
    void setNumber2(std::string number);
    std::string getNumber2() const;
    int getNumber2Len() const {return num2Len;}

    std::string addition();
    std::string subtraction();
    std::string multiplication();
    std::string division();

    calculator operator+(const std::string &s) const;
    calculator operator-(const std::string &s) const;
    calculator operator*(const std::string &s) const;
    calculator operator/(const std::string &s) const;
};


#endif
