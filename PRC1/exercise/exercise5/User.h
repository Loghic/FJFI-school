#ifndef EXERCISE5_USER_H
#define EXERCISE5_USER_H

#include <string>

using std::string; //imports single symbol from std

class User
{
protected:
    string name;
    string surname;
    int uid; //unique id
    //TODO - must return unique value
    int generateUid()
    {
        return 42;
    }
public:
    User(string name, string uid);
    virtual ~User();
    string getName() const{return name;}
    string getSurname() const{return surname;}
    int getUid() const{return uid;}
    void setSurname(string newSurname)
    {
        surname = newSurname;
    }
    void printCommon() const;
    virtual void print() const;
};

class Student : public User
{
protected:
    int credits;
public:
    Student(string name, string surname, int credits);
    virtual ~Student();
    int getCredits() const{return credits;}
    virtual void print() const;
};

class Employee : public User
{
protected:
    int officeNumber;
public:
    Employee(string name, string surname, int officeNumber);
    virtual ~Employee();
    virtual void print() const;
    int getOfficeNumber() const {return officeNumber;}
    void setOfficeNumber(int officeNumber)
    {
        this->officeNumber = officeNumber;
    }

};


#endif //EXERCISE5_USER_H
