#include "calculator.h"
#include "iostream"

calculator::calculator(string n1, string n2)
    : num1(n1), num2(n2)
{
    cout << "Constuctor calculator\n";
}

string reverseString(string s)
{
    string res;
    int j = 0;
    for (int i = s.length()-1; i != -1; i--)
    {
        res.push_back(s[i]);
    }
    return res;
}

int decideNumber(char pos)
{
    switch (pos) {
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case '0':
            return 0;
        default:
            exit(100);
    }
}

int decideNegativeNumber(int pos)
{
    switch (pos) {
        case -9:
            return 1;
        case -8:
            return 2;
        case -7:
            return 3;
        case -6:
            return 4;
        case -5:
            return 5;
        case -4:
            return 6;
        case -3:
            return 7;
        case -2:
            return 8;
        case -1:
            return 9;
        case '0':
            return 0;
        default:
            exit(100);
    }
}

string cycleForAddition(string number1, string number2)
{
    string tmpRes;
    string res;

    int trailingZero = 0;
    for (int i = number1.length()-1; i != -1; i--)
    {
        char pos1 = number1[i];
        char pos2 = number2[i - number1.length() + number2.length()];

        int num1 = decideNumber(pos1);
        int num2 = 0;

        if (pos2 > 0){
            num2 = decideNumber(pos2);
        }


        if (num1 + num2 + trailingZero >= 10){
            string tmp = to_string(num1 + num2 + trailingZero);
            trailingZero = 1;
            tmpRes.push_back(tmp[1]);
        }else{
            string tmp = to_string(num1 + num2 + trailingZero);
            trailingZero = 0;
            tmpRes.push_back(tmp[0]);
        }
    }

    if (trailingZero == 1){
        tmpRes.push_back('1');
    }

    res = reverseString(tmpRes);

    return res;
}

string calculator::addition()
{
    string res;

    if (num1.length() >= num2.length())
    {
        res = cycleForAddition(num1, num2);
    }else
    {
        res = cycleForAddition(num2, num1);
    }

    return res;
}

bool isNumber1BiggerThanNumber2(string n1, string n2)
{
    if(n1.length() > n2.length()){
        return true;
    }else if(n2.length() > n1.length()){
        return false;
    }else{
        int number1 =0, number2 = 0;
        for (int i = n1.length()-1; i != -1; i--)
        {
            if (decideNumber(n2[i]) > decideNumber(n1[i])){
                return false;
            }
        }
        return true;
    }
}

void swapStrings(string &n1, string &n2)
{
    string tmp = n1;
    n1 = n2;
    n2 = tmp;
}

void getRidOfZeroes(string &s)
{
    string tmp;
    int i = s.length()-1;
    for (; i != 0; i--)
    {

        if(s[i] == '0'){
            continue;
        }else{
            break;
        }
    }
    for (int j = 0; j <= i; j++){
        tmp.push_back(s[j]);
    }
    s = tmp;
}


string calculator::subtraction()
{
    string res;
    bool num1Bigger = true;
    if (!isNumber1BiggerThanNumber2(num1, num2))
    {
        num1Bigger = false;
        swapStrings(num1, num2);
    }

    int number1 = 0, number2 = 0, trailingZero = 0;
    int i = num1.length()-1;
    int j = num2.length()-1;
    while (i != -1 && j != -1)
    {
        number1 = decideNumber(num1[i]);
        number2 = decideNumber(num2[j]);


        if (number1 - number2 - trailingZero >= 0){
            string tmp = to_string(number1 - number2 - trailingZero);
            trailingZero = 0;
            res.push_back(tmp[0]);
        }else{
            string tmp = to_string(decideNegativeNumber(number1 - number2 - trailingZero));
            trailingZero = abs(number1-number2);
            res.push_back(tmp[0]);
        }

        i--;
        j--;
    }

    if (i > j){
        number2 = 0;
        for (;i != -1; i--){
            number1 = decideNumber(num1[i]);
            if (number1 - number2 - trailingZero >= 0){
                string tmp = to_string(number1 - number2 - trailingZero);
                trailingZero = 0;
                res.push_back(tmp[0]);
            }else{
                string tmp = to_string(number1 - number2 - trailingZero);
                trailingZero = 1;
                res.push_back(tmp[1]);
            }
        }
    }else if (j > i){
        number1 = 0;
        for (;j != -1; j--){
            number1 = decideNumber(num1[i]);
            if (number1 - number2 - trailingZero >= 0){
                string tmp = to_string(number1 - number2 - trailingZero);
                trailingZero = 0;
                res.push_back(tmp[0]);
            }else{
                string tmp = to_string(number1 - number2 - trailingZero);
                trailingZero = 1;
                res.push_back(tmp[1]);
            }
        }
    }

    getRidOfZeroes(res);
    if (!num1Bigger){
        res.push_back('-');
    }

    return reverseString(res);
}

string calculator::multiplication()
{
    char answ;
    string res;
    cout << "Which number do you want to multiply? Type '1' or '2'" << endl;
    cout << "1 " << num1 << endl;
    cout << "2' " << num2 << endl;
    cin >> answ;
    if (mul == 0){
        res = "0";
    }else if(answ == '1'){
        res = num1;
        for (int i = 1; i < mul; i++){
            setNum2(res);
            res = addition();
        }
    }else if(answ == '2'){
        res = num2;
        for (int i = 1; i < mul; i++){
            setNum1(res);
            res = addition();
        }
    }else{
        cout << "Error the provided action does not exist" << endl;
        exit(100);
    }
    return res;
}
