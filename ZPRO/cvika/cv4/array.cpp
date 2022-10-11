#include <iostream>

using namespace std;

struct Array
{
    double biggestElement; 
    int possitionOfBiggestElement = 0;
    double smallestElement;
    int possitionOfSmallestElement = 0;
    double addtionOfElements;
    double multiplicationOfElements;
};

void print(Array);
Array maxAndMinElement(const double[], const int);
Array AddtionAndMulOfElements(const double[], const int);


int main()
{
    double x[] = {-1.1,2.2,46, 33, -2,3};
    int lenght = sizeof(x)/sizeof(x[0]);
    Array myVector = maxAndMinElement(x,lenght);
    myVector = AddtionAndMulOfElements(x,lenght);
    print(myVector);
    return 0;
}

void print(Array vector)
{
    cout << "The biggest element in vector x is: " << vector.biggestElement << " the possition of the biggest element is: ";
    cout << vector.possitionOfBiggestElement << endl;
    cout << "The smallest element is: " << vector.smallestElement;
    cout << " and the possition of the smallest element is: " << vector.possitionOfSmallestElement << endl;
    cout << "The result of addtion of all elements in vector is: " << vector.addtionOfElements << endl;
    cout << "The result of multiplication of all elements in vector is: " << vector.multiplicationOfElements << endl;
}

Array maxAndMinElement(const double  x[], const int lenght)
{
    Array result;
    result.biggestElement = x[0];
    result.smallestElement = x[0];
    for (int i {0}; i < lenght; i++){
        if (x[i] > result.biggestElement){
            result.biggestElement = x[i]; 
            result.possitionOfBiggestElement = i;
        }else if (x[i] < result.smallestElement){
            result.smallestElement = x[i];
            result.possitionOfSmallestElement = i;
        }
    }
    return result;
}

Array AddtionAndMulOfElements(const double x[], const int lenght)
{
    Array result;
    result.addtionOfElements = 0;
    result.multiplicationOfElements = 1;
    for (size_t i {0}; i < lenght; i++){
        result.addtionOfElements += x[i];
        result.multiplicationOfElements *= x[i];
    }
    return result;
}
