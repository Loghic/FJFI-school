#ifndef LECTURE5_TRIDA_H
#define LECTURE5_TRIDA_H

#include "iostream"

using namespace  std;

template<class T>
class prepravka{
private:
    T data;
public:
    prepravka(T data): data(data){};
    void setData(T data) {this->data = data;}
    T getData() {return data;}
    void vypis();
};

template<class T>
inline void prepravka<T>::vypis()
{
    cout << data;
}

//Partial specialisation for pointer
template<class T>
class prepravka<T*>
//Does not inherit anything, we have to write everything from scratch
//Even thought we want to write new method "vypis"
{
private:
    T* data;
public:
    prepravka(T* data) { setData(data);} // Good programme practice to access Data only using 1 method
    // Not like before with just T
    void setData(T* data){this->data = data;}
    T getData()const {return data;}
    void vypis() {cout << *data;};
};


//complete specialisation
template<>
class prepravka<void>
{
public:
    void vypis() {cout << "Its empty";}
};


#endif //LECTURE5_TRIDA_H
