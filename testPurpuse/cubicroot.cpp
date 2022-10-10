#include <iostream>
using namespace std;

void input(int& number);
void wholeNums(int number);
double thirdPower(double cubic);
void tenthsNums(int number);
void hundrethsNums(int number);
double precision();
void setPrecision(int number);
void setPrecisonFast(int number);

int main()
{
    int number;
    input(number);
    wholeNums(number);
    tenthsNums(number);
    hundrethsNums(number);
    setPrecision(number);
    setPrecisonFast(number);
    cout << "Program has finished!" << endl;
    return 0;
}

void input(int& number)
{
    cout << "Please provide whole possitive number: ";
    cin >> number;
}

void wholeNums(int number)
{
    int i = 1;
    while(thirdPower(i) < number)
    {
        i++;
    }
    cout << "Whole cubic root of number " << number << " is " << i << endl;
}

void tenthsNums(int number)
{
    double i = 0.1;
    while(thirdPower(i) < number)
    {
        i += 0.1;
    }
    cout << "Tenth cubic root of number " << number << " is " << i << endl;
}

void hundrethsNums(int number)
{
    double i = 0.01;
    while(thirdPower(i) < number)
    {
        i+= 0.01;
    }
    cout << "Hundreth cubic root of number " << number << " is " << i << endl;
}

double thirdPower(double cubic)
{
    return cubic * cubic * cubic;
}

double precision()
{
    int precision {0};
    cout << "Please provide precision you would like the number calculate in: ";
    cin >> precision;
    double ans {1};
    for (int i = 0; i < precision; i++)
    {
        ans /= 10;
    }
    return ans;    
}

void setPrecision(int number)
{
    double prec = precision();
    double i = prec;
    while(thirdPower(i) < number)
    {
        i += prec;
    }
    cout << "Cubic root with set preccision of number " << number << " is " << i << endl;
}

void setPrecisonFast(int number)
{
    double prec = precision();
    double i = 1;
    double tmpPrec = 1;
    while(thirdPower(i) < number)
    {
        i += tmpPrec;
        if (thirdPower(i) < number && tmpPrec > prec)
        {
            i -= tmpPrec;
            tmpPrec /= 10;
        }
    }
    cout << "Cubic root fast with set preccision of number " << number << " is " << i << endl;
}
