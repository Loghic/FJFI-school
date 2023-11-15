#include "User.h"
#include <iostream>

using namespace std;

enum {OK};

void sendMail(User *userPtr, string message)
{
    cout << "Sending message\n\n"
        << message
        << "\n\nto the user: \n";
    userPtr->print();
}

void Names(string &name, string &surname)
{
    cout << "Please enter name: ";
    cin >> name;
    cout << "Please enter surname: ";
    cin >> surname;
}

int main()
{
    string name, surname;
    int credits, officeNumber;
    char choice;
    User *u;

    cout << "Welcome to the BLACKBIRD 3000" << endl;
    cout << "Let's create a new user\n";
    cout << "Do you wish to create a new "
         << "(s)tudent or (e)mployee? ";

    cin >> choice;

    Names(name,surname);

    if (choice == 's'){
        cout << "Please, enter initial count of credits: ";
        cin >> credits;
        u = new Student(name, surname, credits);
    } else {
        cout << "Please, enter office number: ";
        cin >> officeNumber;
        u = new Employee(name, surname, officeNumber);
    }

    Employee e(name, surname, 20);
    sendMail(u, "Welcome to the University");


    delete u;
    return OK;
}