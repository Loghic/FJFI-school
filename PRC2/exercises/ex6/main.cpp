#include <iostream>

using namespace std;

void swap(int &n1, int &n2)
{
    cout << "Swap int" << endl;
    int c = n1;
    n1 = n2;
    n2 = c;
}

//void swap_int(int *a, int *b)
//{
//    int *c = a;
//    a = b;
//    b = c;
//}

void swap(float &a, float &b)
{
    cout << "Swap float" << endl;
    float c = a;
    a = b;
    b = c;
}

int main() {
    float number1, number2;
    number1 = -3.2;
    number2 = 10.5;
    int numero1 = 3;
    int numero2 = 5;
    cout << "Pre-swap: " << endl;
    cout << "Number1: " <<  number1 << ", Number2: " << number2 << endl;
    cout << "Numero1: " <<  numero1 << ", Numero2: " << numero2 << endl;
    swap(number1, number2);
    swap(numero1, numero2);
//    swap(numero1, number2);
    cout << "Post-swap: " << endl;
    cout << "Number1: " <<  number1 << ", Number2:  " << number2 << endl;
    cout << "Numero1: " <<  numero1 << ", Numero2: " << numero2 << endl;
}
