#include <iostream>
using namespace std;

bool Even(int number);
bool prime(int number);
void printEven(bool,int);
void printPrime(bool,int);
bool primeWithBreak(int number);

int main()
{
    int number{0};
    cout << "Please enter whole number: ";
    cin >> number;
    printEven(Even(number),number);
    cout << "Please enter whole possitive number to know if its prime number: ";
    cin >> number;
    printPrime(prime(number), number);
    printPrime(primeWithBreak(number), number);
    return 0;
}

bool Even(int number)
{
    if (number % 2 == 0){
        return true;
    }return false;
}

bool prime(int number) // prime with return
{
    if (number < 2){
        return false;
    }
    for (int i = 2; i*i <= number; i++){
        if (number % i == 0){
            return false;
        }
    }return true;
}

void printEven(bool isEven, int number)
{
    if(isEven){
            cout << "Number " << number << " is even" << endl;
        }else{
            cout << "Number " << number << " is odd" << endl;
        }
}

void printPrime(bool isPrime, int number)
{
    if(isPrime){
        cout << "Number " << number << " is prime number" << endl;
    }else{
        cout << "Number " << number << " is not prime number" << endl;
    }
}

bool primeWithBreak(int number) // for cycle with break
{
    bool isPrime = true;
    if (number < 2){
        return false;
    }
    for (int i = 2; i*i <= number; i++){
        if (number % i == 0){
            isPrime = false;
            break;
        }
    }return isPrime;
}