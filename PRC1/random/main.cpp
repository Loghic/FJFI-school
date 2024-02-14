#include <iostream>
#include "array.h"

const int SIZE = 5;

void print(array arr)
{
    for (int i = 0; i < arr.getSize(); i++){
        std::cout << arr.getNumberOnIteratorPossition(i) << std::endl;
    }
}


int main() {
    array arr (SIZE);

//    std::cout << "Hello, World!" << std::endl;

    print(arr);
    return 0;
}
