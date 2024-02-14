#include "BigInt.h"
#include "vector"

using namespace std;

const int LLI_MAX_LEN = to_string(LLONG_MAX).length();
const int OVERFLOWING_DECIMAL_NUMBER = 10;


//Default constructor
BigInt::BigInt() {
    value = "0";
    sign = '+';
}

//Copy constructor
BigInt::BigInt(const BigInt& number) {
    value = number.value;
    sign = number.sign;
}

//Int to BigInt
BigInt::BigInt(const long long& number) {
    value = std::to_string(std::abs(number));
    if (number < 0)
        sign = '-';
    else
        sign = '+';
}

bool isValidNumber(string s)
{
    for (int i = 0; i < s.length(); i++){
        if (s[i] < '0' || s[i] > '9'){
            return false;
        }
    }
    return true;
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

//String to BigInt
BigInt::BigInt(const string& number) {
    if (number[0] == '+' or number[0] == '-') {     // check for sign
        string withoutSign = number.substr(1);
        if (isValidNumber(withoutSign)) {
            value = withoutSign;
            sign = number[0];
        }
        else {
            cerr << "Not a number!" << endl;
            exit(100);
        }
    }
    else {      // if no sign is specified
        if (isValidNumber(number)) {
            value = number;
            sign = '+';
        }
        else {
            cerr << "Not a number!" << endl;
            exit(100);
        }
    }
}

//BigInt = BigInt
BigInt& BigInt::operator=(const BigInt& number) {
    value = number.value;
    sign = number.sign;

    return *this;
}

//BigInt = int
BigInt& BigInt::operator=(const long long int& number) {
    BigInt tmp(number);
    value = tmp.value;
    sign = tmp.sign;

    return *this;
}

//BigInt = String
BigInt& BigInt::operator=(const string& number) {
    BigInt tmp(number);
    value = tmp.value;
    sign = tmp.sign;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.sign == '-')
        out << num.sign;
    out << num.value;

    return out;
}

BigInt BigInt::operator+() const
{
    return *this;
}
BigInt BigInt::operator-() const
{
    BigInt tmp;

    tmp.value = this->value;
    if (value != "0") {
        if (sign == '+')
            tmp.sign = '-';
        else
            tmp.sign = '+';
    }
    return tmp;
}

string BigInt::to_string() const {
    // prefix with sign if negative
    return this->sign == '-' ? "-" + this->value : this->value;
}

bool isNum1BiggerThanNum2(const string &num1, const string &num2)
{
    if (num1.size() > num2.size()){
        return true;
    }else if(num2.size() > num1.size()){
        return false;
    }else{
        for (int i = 0; i < num1.size(); i++) {
            if (num2[i] > num1[i]){
                return false;
            }else if(num1[i] > num2[i]){
                return true;
            }
        }
    }
    return true;
}

BigInt BigInt::operator+(const BigInt& number) const {
    // If numbers are different signs, subtract
    if (this->sign == '+' and number.sign == '-') {
        BigInt newNum = number;
        newNum.sign = '+';
        return *this - newNum;
    }
    else if (this->sign == '-' and number.sign == '+') {
        BigInt newNum = *this;
        newNum.sign = '+';
        return -(newNum - number);
    }

    string bigger, smaller;
    if (isNum1BiggerThanNum2(this->value, number.value)){
        bigger = this->value;
        smaller = number.value;
    }else{
        bigger = number.value;
        smaller = this->value;
    }

    BigInt res;      // the resultant sum
    res.value = "";  // the value is cleared as the digits will be appended
    int trailingZero = 0;
    int iteratorNumber1 = bigger.size()-1;
    int iteratorNumber2 = smaller.size()-1;
    for (;iteratorNumber2 > -1; iteratorNumber1--,iteratorNumber2--) {
        int sum = bigger[iteratorNumber1] - '0' + smaller[iteratorNumber2] - '0' + trailingZero;
        res.value = std::to_string(sum % 10) + res.value;
        trailingZero = sum / 10;
    }
    if (iteratorNumber1 > -1){
        for(; iteratorNumber1 > -1; iteratorNumber1--) {
            int sum = bigger[iteratorNumber1] - '0' + trailingZero;
            res.value = std::to_string(sum % 10) + res.value;
            trailingZero = sum / 10;
        }
    }
    if (trailingZero)
        res.value = std::to_string(trailingZero) + res.value;

    // if the operands are negative, the result is negative
    if (this->sign == '-' and res.value != "0")
        res.sign = '-';

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

BigInt BigInt::operator-(const BigInt& number) const {
    // if the operands are of opposite signs, perform addition
    if (this->sign == '+' and number.sign == '-') {
        BigInt newNum = number;
        newNum.sign = '+';
        return *this + newNum;
    }
    else if (this->sign == '-' and number.sign == '+') {
        BigInt newNum = *this;
        newNum.sign = '+';
        return -(newNum + number);
    }

    BigInt res;

    string bigger, smaller;
    char bigSign, smallSign;
    if (isNum1BiggerThanNum2(this->value, number.value)){
        bigger = this->value;
        bigSign = this->sign;
        smaller = number.value;
        smallSign = number.sign;
    }else{
        bigger = number.value;
        bigSign = number.sign;
        smaller = this->value;
        smallSign = this->sign;
    }

    res.value = "";  // the value is cleared as the digits will be appended
    int trailingZero = 0;
    int iteratorNumber1 = bigger.size() -1;
    int iteratorNumber2 = smaller.size() - 1;
    // subtract the two values
    for (;iteratorNumber2 != -1; iteratorNumber1--, iteratorNumber2-- ) {
        int diff = bigger[iteratorNumber1] - smaller[iteratorNumber2] - trailingZero;
        if (diff >= 0) {
            trailingZero = 0;
            res.value.push_back(std::to_string(diff)[0]);
        }else{
            trailingZero = 1;
            res.value.push_back(std::to_string(decideNegativeDigit(diff))[0]);
        }
    }

    if (iteratorNumber1 > -1){
        for (; iteratorNumber1 != -1; iteratorNumber1--){
            int num1MinusTrailingZero = bigger[iteratorNumber1] -'0' - trailingZero;
            if (num1MinusTrailingZero >= 0){
                trailingZero = 0;
                res.value.push_back(std::to_string(num1MinusTrailingZero)[0]);
            }else{
                trailingZero = 1;
                res.value.push_back(std::to_string(decideNegativeDigit(num1MinusTrailingZero))[0]);
            }
        }
        if (trailingZero == 1){
            res.value.push_back(std::to_string(trailingZero)[0]);
        }
    }

    getRidOfZeroes(res.value);
    if ((this->value == bigger && bigSign == '-')
        || (bigger == number.value && smallSign == '+')){
        res.sign = '-';
    }
    if (res.value == "0")
        res.sign = '+';

    std::reverse(res.value.begin(), res.value.end());
    return res;
}

BigInt BigInt::operator*(const BigInt& number) const
{
    int num1Len = this->value.size();
    int num2Len = number.value.size();
    if ((num1Len == 1 && this->value[0] == '0')
    || (num2Len == 1 && number.value[0] == '0'))
        return BigInt(0);
    if (num1Len == 1 && this->value[0] == '1')
        return number;
    if (num2Len == 1 && number.value[0] == '1')
        return *this;

    vector<int> tmp;
    for (int i = 0; i < num1Len + num2Len;i++){
        tmp.push_back(0);
    }
    int iteratorTmp = 0;
    int trailingZero = 0;
    BigInt res;
    for (int iteratorNumber1 = num1Len-1; iteratorNumber1 != -1; iteratorNumber1--)
    {
        iteratorTmp = num1Len - 1 - iteratorNumber1;
        for (int iteratorNumber2 = num2Len-1; iteratorNumber2 != -1; iteratorNumber2--)
        {
            int num1MulNum2 = (this->value[iteratorNumber1] - '0')
                    * (number.value[iteratorNumber2] - '0') + trailingZero;

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

    res.value = "";
    for (int i = 0; i < num1Len + num2Len; i++){
        res.value.push_back(std::to_string(tmp[i])[0]);
    }
    getRidOfZeroes(res.value);
    std::reverse(res.value.begin(), res.value.end());
    if (this->sign != number.sign){
        res.sign = '-';
    }

    return res;
}

bool isPowerOf10(string number){

    if (number[0] != '1')
        return false;
    for (size_t i = 1; i < number.size(); i++)
        if (number[i] != '0')
            return false;

    return true;    // first digit is 1 and the following digits are all 0
}

bool areNumber1AndNumber2Equal(string number1, string number2)
{
    if (number1.size() != number2.size()){
        return false;
    }
    for (int i = 0; i < number1.size(); i++) {
        if (number1[i] != number2[i]) {
            return false;
        }
    }
    return true;
}

BigInt BigInt::operator/(const BigInt& number) const
{
        BigInt res;
        res.value = "";
        int num1Len = this->value.size();
        int num2Len = number.value.size();
        if (num2Len == 1 && number.value[0] == 0)
            throw std::logic_error("Attempted division by zero");

        if (num2Len >= num1Len && !isNum1BiggerThanNum2(this->value, number.value))
            return BigInt(0);

        if (num2Len == 1 && number.value[0] == 1) {
            for (int i = 0; i < num1Len; i++) { res.value.push_back(std::to_string(this->value[i])[0]); }
            if ((this->sign != number.sign))
                res.sign = '-';
            return res;
        }


        if (num1Len < LLI_MAX_LEN && num2Len < LLI_MAX_LEN)
            res = std::to_string(stoll(this->value) / stoll(number.value));
        else if (areNumber1AndNumber2Equal(this->value, number.value))
            res = "1";
        else if (isPowerOf10(number.value)) { // if divisor is a power of 10 do optimised calculation
            size_t digits_in_quotient = num1Len - num2Len;
            for (size_t i = 0; i <= digits_in_quotient; i++){res.value = res.value + this->value[i] ;}
        }
        else {
            int idx = 0;
            BigInt tmp;
            tmp = "";
            tmp.value.push_back(this->value[idx]);
            while (idx < num1Len-1 && (num2Len > idx+1 ||
            (isNum1BiggerThanNum2(number.value, tmp.value) &&
            !areNumber1AndNumber2Equal(number.value, tmp.value))))
                tmp.value.push_back(this->value[++idx]);

            // Repeatedly divide divisor with temp. After
            // every division, update temp to include one
            // more digit.
            while (num1Len > idx) {
                int cnt = 0;
                string convert;
                while(tmp.value.size() > num2Len ||
                      (tmp.value.size() == num2Len && isNum1BiggerThanNum2(tmp.value, number.value))){
                    tmp = tmp-number;
                    cnt++;
                }
                res.value += cnt + '0';
                // adding the next digit to the dividend
                tmp.value.push_back(this->value[++idx]);
            }
        }


        if (this->sign != number.sign){
            res.sign = '-';
        }

    if (res.value[0] == '0'){
        std::reverse(res.value.begin(), res.value.end());
        getRidOfZeroes(res.value);
        std::reverse(res.value.begin(), res.value.end());
    }

    return res;
}
