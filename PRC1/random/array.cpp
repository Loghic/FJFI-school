#include "iostream"

#include "array.h"

array::array()
    :buff(nullptr), size(0)
{
    std::cout << "Constructor";
}
array::~array()
{
    delete []buff;
    buff = nullptr;
    size = 0;
    std::cout << "Destructor\n";
}

array::array(int capacity)
    : size(capacity)
{
    buff = new int [size];
    for (int i = 0; i < size; i++){
        buff[i] = i;
    }
    std::cout << "Constructor with parameters\n";
}

//Copy constructor
array::array(const array& number)
{
    size = number.size;
    buff = new int [size];
    for (int i = 0; i < size; i++){
        buff[i] = number.buff[i];
    }
}


int *array::getBuff() const {
    return buff;
}

void array::setBuff(int *buff) {
    array::buff = buff;
}

int array::getSize() const {
    return size;
}

void array::setSize(int size) {
    array::size = size;
}

