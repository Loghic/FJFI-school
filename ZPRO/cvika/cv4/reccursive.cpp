#include <iostream>

using namespace std;

enum {OK , ERROR_INPUT = 100,};

int factorial(int, int);

int main()
{
    int number {0};
    cout << "Enter positive int, max 12: ";
    cin >> number;
    if (number < 0 || number > 12){
        cout << "Wrong input!" << endl;
        return ERROR_INPUT;
    }
    int sum {1};
    sum = factorial(number, sum);
    cout << "The factorial of number " << number << " is: " << sum << endl;
    return OK;
}

int factorial(int number, int sum)
{
    if (number == 1 || number == 0){
        return sum;
    }else{
        sum *= number;
        number--;
        sum = factorial(number, sum);
        return sum;
    }
}
