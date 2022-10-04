#include "flatterrer.hpp"
#include <iostream>

using namespace std;

void flatterring()
{
    string name;
    cout << "Enter your name: ";
    cin >> name;
    int age;
    cout << "Enter your age: ";
    cin >> age;
    if (age < 20){
        cout << name << ", you are very young!" << endl;
    }else{
        cout << name << ", you are still very young!" << endl;
    }
}

int input(int &number, int &option)
{
    cout << "Please provide number you want to know faktorial of (max 12): ";
    cin >> number;
    if (number < 0 || number > 12){
        cout << "Incorrect input!" << endl;
        return 1;
    }
    cout << "Choose option 0 For cycle, 1 While cycle: ";
    cin >> option;
    if (option == 1 || option == 0){
        return 0;
    }else{
        cout << "Invalid option!" << endl;
        return 1;
    }
    // (option ? faktorialWhile(number) : faktorialFor(number));
}

int faktorialWhile(int number)
{
    int res = 1;
    while (number)
    {
        res *= number--;
    }
    return res;
}

int faktorialFor(int number)
{
    int res = 1;
    for (size_t i {2}; i <= number; i++){
        res *= i;
    }
    return res;
}

void faktorial(int number, int option)
{
    int res = 1;
    if (option){
        while (number)
        {
            res *= number--;
        }
        cout << "Faktorial using WHILE: " << res << endl;
        
    }else{
        for (size_t i {2}; i <= number; i++){
            res *= i;
        }
        cout << "Faktorial using FOR: " << res << endl;
    }
}