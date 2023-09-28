#include <iostream>

using namespace std;

enum {OK, ERROR = 100};

void myinput(long long int &a, long long int &b);
long long int gcd(long long int a, long long int b);
long long int scm(long long int res, long long int a, long long int b);
void print(long long int resGCD, long long int resSCM);

int main()
{

    long long int number1 = 1;
    long long int number2 = 1;
    
    for (long long int i = 0; i < 20; i++){
        number1 *= 2;
    }
    
    for (long long int j = 0; j < 30; j++){
        number2 *= 2;
    }
    
    number1--;
    number2--;

    long long int resGCD = gcd(number1, number2);

    long long int resSCM = scm(resGCD, number1, number2);

    print(resGCD, resSCM);

    return OK;
}

void myinput(long long int &a, long long int &b)
{
    cout << "Please provide 2 whole numbers: ";
    cin >> a >> b;
}

long long int gcd(long long int a, long long int b)
{
    long long int r = 0;

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

long long int scm(long long int res, long long int a, long long int b)
{
    return a*b/res;
}

void print(long long int resGCD, long long int resSCM)
{
    cout << "GCD is: " << resGCD << endl;
    cout << "SCM is: " << resSCM << endl;
}

