#include <iostream>

using namespace std;

enum {OK, ERROR = 100};

void myinput(int &a, int &b);
int gcd(int a, int b);
int scm(int res, int a, int b);
void print(int resGCD, int resSCM);

int main()
{

    int number1;
    int number2;
    myinput(number1, number2);

    int resGCD = gcd(number1, number2);

    int resSCM = scm(resGCD, number1, number2);

    print(resGCD, resSCM);

    return OK;
}

void myinput(int &a, int &b)
{
    cout << "Please provide 2 whole numbers: ";
    cin >> a >> b;
}

int gcd(int a, int b)
{
    int r = 0;

    if (a < b){
        r = b;
        b = a;
        a = r;
    }

    while (b != 0){
        r = a%b;
        a = b;
        b = r;
    }
    return a;
}

int scm(int res, int a, int b)
{
    return a*b/res;
}

void print(int resGCD, int resSCM)
{
    cout << "GCD is: " << resGCD << endl;
    cout << "SCM is: " << resSCM << endl;
}

