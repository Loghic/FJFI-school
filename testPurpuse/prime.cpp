#include <iostream>
using namespace std;

int main()
{
    int input;
    cout << "Please provide whole possitive number: ";
    cin >> input;

    bool prime = true;
    int i = 2;
    if (input < 2){
        prime = false;
    }

    while (i*i <= input){
        if (input % i == 0){
            prime = false;
            break;
        }
        i++;
    }
    cout << "The number " << input << (prime ? " is prime" : " isnt prime") << endl;
}