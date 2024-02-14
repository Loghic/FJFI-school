#include "calculator.h"
#include "iostream"

using namespace std;

const int LLI_MAX_LEN = to_string(LONG_LONG_MAX).length();

const int OVERFLOWING_DECIMAL_NUMBER = 10;

calculator::calculator()
{
    num1Len = 0, num2Len = 0;
    cout << "Constructor\n";
}

calculator::calculator(std::string number1, std::string number2)
{
    setNumber1(std::move(number1));
    setNumber2(std::move(number2));
    cout << "Constructor with parameters\n";
}

calculator::~calculator()

{
    cout << "Destructor\n";
}

int numberIntValue(char digit)
{
    if (digit < '0' || digit > '9'){
        cerr << "Given number doesn't consist of only numbers!" << endl;
        exit(100);
    }
    return digit - '0';
}

void calculator::setNumber1(std::string number)
{
    num1.clear();
    int iterator = 0;
    num1Len = number.length();
    if (number[0] == '-'){
        num1Plus = false;
        iterator++;
        num1Len--;
    }else if(number[0] == '+'){
        num1Plus = true;
        iterator++;
        num1Len--;
    }else{
        num1Plus = true;
    }

    for (; iterator < number.length(); iterator++) {
        num1.push_back(numberIntValue(number[iterator]));
    }

}

std::string calculator::getNumber1() const
{
    string ret;
    if (!num1Plus){
        ret.push_back('-');
    }
    for (int i = 0; i < num1Len; i++) ret.push_back(to_string(num1[i])[0]);
   return ret;
}

void calculator::setNumber2(std::string number)
{
    num2.clear();
    num2Len = number.length();
    int iterator = 0;
    if (number[0] == '-'){
        num2Plus = false;
        iterator++;
        num2Len--;
    }else if(number[0] == '+'){
        num2Plus = true;
        iterator++;
        num2Len--;
    }else{
        num2Plus = true;
    }

    for (; iterator < number.length(); iterator++) {
        num2.push_back(numberIntValue(number[iterator]));
    }
}

std::string calculator::getNumber2() const
{
    string ret;
    if (!num2Plus){
        ret.push_back('-');
    }
    for (int i = 0; i < num2Len; i++) ret.push_back(to_string(num2[i])[0]);
    return ret;
}

string additionPlusPlus(vector<int> n1, vector<int> n2, int n1Len, int n2Len)
{
    string res;
    int iteratorNumber1 = n1Len -1;
    int iteratorNumber2 = n2Len -1;
    int trailingZero = 0;
    //This is done until all the digits of either number has been added
    for (; iteratorNumber1 != -1 && iteratorNumber2 != -1;iteratorNumber1--, iteratorNumber2--)
    {
        int num1PlusNum2 = n1[iteratorNumber1] + n2[iteratorNumber2] + trailingZero;
        if (num1PlusNum2 >= OVERFLOWING_DECIMAL_NUMBER){
            trailingZero = 1;
        }else{
            trailingZero = 0;
        }
        res.push_back(to_string(num1PlusNum2 % 10)[0]);
    }

    //If one of the numbers is longer than the others this will happen after the main for cycle
    if (iteratorNumber1 > -1)
    {
        for (; iteratorNumber1 != -1; iteratorNumber1--){
            int num1PlusTrailingZero = n1[iteratorNumber1] + trailingZero;
            if (num1PlusTrailingZero >= OVERFLOWING_DECIMAL_NUMBER){
                trailingZero = 1;
            }else{
                trailingZero = 0;
            }
            res.push_back(to_string(num1PlusTrailingZero % 10)[0]);
        }
        if (trailingZero == 1){
            res.push_back(to_string(trailingZero)[0]);
        }
    }else{
        for (; iteratorNumber2 != -1; iteratorNumber2--){
            int num2PlusTrailingZero = n2[iteratorNumber2] + trailingZero;
            if (num2PlusTrailingZero >= OVERFLOWING_DECIMAL_NUMBER){
                trailingZero = 1;
            }else{
                trailingZero = 0;
            }
            res.push_back(to_string(num2PlusTrailingZero % 10)[0]);
        }
        if (trailingZero == 1){
            res.push_back(to_string(trailingZero)[0]);
        }
    }

    return res;
}

int decideNegativeDigit(int digit)
{
    switch (digit) {
        case -1:
            return 9;
        case -2:
            return 8;
        case -3:
            return 7;
        case -4:
            return 6;
        case -5:
            return 5;
        case -6:
            return 4;
        case -7:
            return 3;
        case -8:
            return 2;
        case -9:
            return 1;
        case 0:
        case -10:
            return 0;
        default:
            cerr << "Given number doesn't consist of only numbers!" << endl;
            exit(100);

    }
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

bool isNum2BiggerThanNum1(vector<int> const& number1, vector<int> const& number2, int len)
{
    for (int i = 0; i < len; i++){
        if (number1[i] > number2[i]){
            return false;
        }else if(number2[i] > number1[i]){
            return true;
        }
    }
    return true;
}

bool areNumber1AndNumber2Equal(vector <int> const& number1, vector<int> const& number2,
                               int number1Len, int number2Len)
{
    if (number1Len != number2Len){
        return false;
    }
    for (int i = 0; i < number1Len; i++) {
        if (number1[i] != number2[i]) {
            return false;
        }
    }
    return true;
}

string subtractionPlusPlus(vector<int> &n1, vector<int> &n2, int n1Len, int n2Len)
{
    string res;
    int iteratorNumber1 = n1Len -1;
    int iteratorNumber2 = n2Len -1;
    int trailingZero = 0;
    vector<int> biggerNumber = n1;
    vector<int> smallerNumber = n2;

    if (n2Len > n1Len || (n1Len == n2Len && isNum2BiggerThanNum1(n1, n2, n1Len))){
        biggerNumber = n2;
        smallerNumber = n1;
        iteratorNumber1 = n2Len-1;
        iteratorNumber2 = n1Len -1;
    }

    for (;iteratorNumber2 != -1; iteratorNumber1--, iteratorNumber2--){
        int num1MinusNum2 = biggerNumber[iteratorNumber1] - smallerNumber[iteratorNumber2] - trailingZero;
        if (num1MinusNum2 >= 0){
            trailingZero = 0;
            res.push_back(to_string(num1MinusNum2)[0]);
        }else{
            trailingZero = 1;
            res.push_back(to_string(decideNegativeDigit(num1MinusNum2))[0]);
        }
    }

    if (iteratorNumber1 > -1)
    {
        for (; iteratorNumber1 != -1; iteratorNumber1--){
            int num1MinusTrailingZero = biggerNumber[iteratorNumber1] - trailingZero;
            if (num1MinusTrailingZero >= 0){
                trailingZero = 0;
                res.push_back(to_string(num1MinusTrailingZero)[0]);
            }else{
                trailingZero = 1;
                res.push_back(to_string(decideNegativeDigit(num1MinusTrailingZero))[0]);
            }
        }
        if (trailingZero == 1){
            res.push_back(to_string(trailingZero)[0]);
        }
    }

    getRidOfZeroes(res);
    return res;
}

std::string calculator::addition()
{
    string res;

    if (num1Plus && num2Plus){
        res = additionPlusPlus(num1, num2, num1Len, num2Len);
    }else if(!num1Plus && !num2Plus){
        res = additionPlusPlus(num1, num2, num1Len, num2Len);
        res.push_back('-');
    }else{
        if ((num2Len > num1Len) || (num1Len == num2Len &&
        isNum2BiggerThanNum1(num1, num2, num1Len))){
            res = subtractionPlusPlus(num2, num1, num2Len, num1Len);
            //If number2 is bigger in absolute value and also negative
            if (!num2Plus){
                res.push_back('-');
            }
        }else{
            res = subtractionPlusPlus(num1, num2, num1Len, num2Len);
            //If number1 is bigger in absolute value and negative
            if (!num1Plus){
                res.push_back('-');
            }
        }
    }

    //reverses the string
    std::reverse(res.begin(), res.end());
    return res;
}

std::string calculator::subtraction()
{
    string res;

    if (num1Plus && num2Plus){
        //Either number2 is longer than number1 or is bigger than number1
        if ((num2Len > num1Len) || (num1Len == num2Len
        && isNum2BiggerThanNum1(num1, num2, num1Len))){
            res = subtractionPlusPlus(num2, num1, num2Len, num1Len);
            res.push_back('-');
        }else{
            res =subtractionPlusPlus(num1, num2, num1Len, num2Len);
        }
    }else if(num1Plus != num2Plus){
        res = additionPlusPlus(num1, num2, num1Len, num2Len);
        if (!num1Plus){
            res.push_back('-');
        }
    }else{
        if ((num2Len > num1Len) || (num1Len == num2Len
        && isNum2BiggerThanNum1(num1, num2, num1Len))){
            res = subtractionPlusPlus(num2, num1, num2Len, num1Len);

        }else{
            res =subtractionPlusPlus(num1, num2, num1Len, num2Len);
            res.push_back('-');
        }
    }

    std::reverse(res.begin(), res.end());
    return res;
}

std::string calculator::multiplication()
{
    string res;
    int trailingZero = 0;
    vector<int> tmp;
    for (int i = 0; i < num1Len+num2Len; i++){
        tmp.push_back(0);
    }

    int iteratorTmp = 0;
    for (int iteratorNumber1 = num1Len-1; iteratorNumber1 != -1; iteratorNumber1--)
    {
        iteratorTmp = num1Len - 1 - iteratorNumber1;
        for (int iteratorNumber2 = num2Len-1; iteratorNumber2 != -1; iteratorNumber2--)
        {
            int num1MulNum2 = num1[iteratorNumber1] * num2[iteratorNumber2] + trailingZero;

            if (num1MulNum2 >= OVERFLOWING_DECIMAL_NUMBER){
                trailingZero = num1MulNum2 / 10;
            }else{
                trailingZero = 0;
            }

            if ((tmp[iteratorTmp] + (num1MulNum2 % 10)) >= OVERFLOWING_DECIMAL_NUMBER){
                trailingZero++;
            }
            tmp[iteratorTmp] = (tmp[iteratorTmp] + (num1MulNum2 % 10)) % 10;
            iteratorTmp++;
        }
        tmp[iteratorTmp] = trailingZero;
        trailingZero = 0;
    }

    for (int i = 0; i < num1Len+num2Len; i++){
        res.push_back(to_string(tmp[i])[0]);
    }

    getRidOfZeroes(res);
    if (num1Plus != num2Plus){
        res.push_back('-');
    }
    std::reverse(res.begin(), res.end());
    return res;
}

bool isPowerOf10(vector<int> const num, int numLen){
    if (num[0] != 1)
        return false;
    for (size_t i = 1; i < numLen; i++)
        if (num[i] != 0)
            return false;

    return true;    // first digit is 1 and the following digits are all 0
}

std::string calculator::division() {
    string res;

    if (num2Len == 1 && num2[0] == 0)
        throw std::logic_error("Attempted division by zero");

    if (num2Len > num1Len && isNum2BiggerThanNum1(num1, num2, num1Len))
        return "0";

    if (num2Len == 1 && (num2Plus == num1Plus) && num2[0] == 1) {
        for (int i = 0; i < num1Len; i++) { res.push_back(to_string(num1[i])[0]); }
        return res;
    }

    if (num2Len == 1 && num2[0] == 1 && (num1Plus != num2Plus)) {
        res.push_back('-');
        for (int i = 0; i < num1Len; i++) { res.push_back(to_string(num1[i])[0]); }
        return res;
    }

    if (num1Len < LLI_MAX_LEN && num2Len < LLI_MAX_LEN)
        res = to_string(stoll(getNumber1()) / stoll(getNumber2()));
    else if (areNumber1AndNumber2Equal(num1,num2,num1Len,num2Len))
        res = "1";
    else if (isPowerOf10(num2,num2Len)) { // if divisor is a power of 10 do optimised calculation
        size_t digits_in_quotient = num1Len - num2Len;
        for (size_t i = 0; i <= digits_in_quotient; i++){res.push_back(to_string(num1[i])[0]);}
    }
    else {
        int idx = 0;
        vector<int> tmp;
        tmp.push_back(num1[idx]);
        while (idx < num1Len-1 && (num2Len > idx+1 ||
        (isNum2BiggerThanNum1(tmp, num2, num2Len) &&
        !areNumber1AndNumber2Equal(tmp,num2,num2Len,idx+1))))
            tmp.push_back(num1[++idx]);

        // Repeatedly divide divisor with temp. After
        // every division, update temp to include one
        // more digit.
        while (num1Len > idx) {
            int cnt = 0;
            string convert;
            while(tmp.size() > num2Len ||
            (tmp.size() == num2Len && isNum2BiggerThanNum1(num2, tmp, num2Len))){
                convert = subtractionPlusPlus(tmp, num2, tmp.size(), num2Len);
                tmp.clear();
                std::reverse(convert.begin(), convert.end());
                for (int i = 0; i < convert.length();i++){tmp.push_back(numberIntValue(convert[i]));}
                cnt++;
            }
            res += cnt + '0';
            // adding the next digit to the dividend
             tmp.push_back(num1[++idx]);
        }
    }


    if (num1Plus != num2Plus){
        std::reverse(res.begin(), res.end());
        res.push_back('-');
        std::reverse(res.begin(), res.end());
    }

    return res;
}

calculator calculator::operator+(const string &s) const
{
    set
}

calculator calculator::operator-(const calculator&) const
{

}
calculator calculator::operator*(const calculator&) const
{

}
calculator calculator::operator/(const calculator&) const
{

}

