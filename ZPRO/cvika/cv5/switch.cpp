#include <iostream>
using namespace std;

void days();
void letter();

int main()
{
    days();
    letter();

    return 0;
}

void days()
{
    int number;
    cout << "Enter a number: ";
    cin >> number;

    switch (number){
        case 1: 
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3: 
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5: 
            cout << "Friday" << endl;
            break;
        case 6:
            cout << "Saturday" << endl;
            break;
        case 7:
            cout << "Sunday" << endl;
            break;
        default:
            cout << "Uknown day" << endl;
            break;
    }   
}

void letter()
{
    char c;
    cout << "Enter a character: ";
    cin >> c;
    if(('a' <= c) && (c <= 'z')){
        cout << "You have entered small letter" << endl;
    }else if(('A' <= c) && (c <= 'Z')){
        cout << "You have entered big letter" << endl;
    }else if (('0' <= c) && (c <= '9')){
        cout << "You have entered number" << endl;
    }else{
        cout << "You have entered this char: " << c << endl;
    }
}