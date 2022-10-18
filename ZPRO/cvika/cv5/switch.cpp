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
    int day;
    cout << "Enter a number: "; // each number is assigned to some day
    cin >> day;

    switch (day){
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

void letter() // Tells you what type of character you have typed, if its known type
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