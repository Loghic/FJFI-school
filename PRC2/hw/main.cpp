#include <iostream>

using namespace std;

template <typename T> float sqrt_root(T x, int precision);
float decimalPrecision(int precision);

int main()
{
    float number;
    int precision;
    cout << "Hello please provide the number you want to know the square root of: ";
    cin >> number;
    cout << "\nPlease provide precision with regards to decimal places: ";
    cin >> precision;
    cout << sqrt_root(number, precision) << endl;
    return 0;
}

float decimalPrecision(int precision)
{
    float res = 1;
    for (int i = 0; i < precision; i++){
        res /= 10;
    }
    return res;
}

template <typename T> float sqrt_root(T x, int precision)
{
    float Fa = 0;
    float Fb = float(x);
    float Fc = 0;
    bool shouldContinue = true;
    float dPrecision = decimalPrecision(precision);
    while (shouldContinue){
        Fc = (Fa + Fb) / 2;
        if (Fc*Fc > x + dPrecision){
            Fb = Fc;
        }else if (Fc*Fc < x - dPrecision){
            Fa = Fc;
        }else{
            shouldContinue = false;
        }
    }
    return Fc;
}
