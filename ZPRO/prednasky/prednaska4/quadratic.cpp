#include <iostream>
#include <math.h>

using namespace std;

enum struct Type{Real, Complex};
enum {a1 , b1 , c1 , x1=0 , x2};

struct Result
{
    Type myType;
    double result[2]{};

};

Result ResOfQuadraticEquation(double coefficient[])
{
    double a = coefficient[a1];
    double b = coefficient[b1];
    double c = coefficient[c1];
    bool pDiscriminat = true; // possitve discriminant
    
    double d = b*b - 4*a*c; // discriminant
    (d >= 0 ? pDiscriminat = true : pDiscriminat = false);
    Result result;
    d = sqrt(abs(d));
    double pNumerator = -b + d; // positive numberator
    double nNumerator = -b - d; // negative numerator
    double denominator = 2 * a; 
    if (pDiscriminat){
        result.myType=Type::Real;
        result.result[x1] = pNumerator / denominator;
        result.result[x2] = nNumerator / denominator;
    }else{
        result.myType=Type::Complex;
        result.result[x1] = pNumerator / denominator;
        result.result[x2] = nNumerator / denominator;
    }
    
    return result;
}

int main()
{
    double equation[]{1,1,1};
    cout << "Enter coefficients of quadratic equation in form 'a' 'b' 'c' : ";
    cin >> equation[a1] >> equation[b1] >> equation[c1];
    Result result = ResOfQuadraticEquation(equation);
    if (result.myType == Type::Real){
        cout << "x1: " << result.result[x1] << " x2: " << result.result[x2] << endl;
    }else{
        cout << "x1: " << result.result[x1] << "i x2: "<< result.result[x2] << "i" << endl;
    }
    return 0;
}
