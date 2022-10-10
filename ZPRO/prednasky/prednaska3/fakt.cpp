#include <iostream>
using namespace std;

enum {ERROR = 100};

using T = double;
const int CELLING_FOR_FACTORIAL = 12;

T factorial(T number)
{
    T result = 1;
    while (number > 1)
    {
        result *= number--;
    }
    return result;
}

int main()
{
    cout << "Enter integer: ";
    int number;
    cin >> number;
    if ((number >= 0) && (number <= CELLING_FOR_FACTORIAL)){
        cout << "The faktorial is: " << factorial(number) << endl;
    }else{
        cout << "The number is out of range!" << endl;
        return ERROR;
    }

    return 0;
}
