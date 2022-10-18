#include <iostream>
using namespace std;

void bubbleSortHigh(int[],int);
void bubbleSortLow(int[],int);
void print(int[],int);

int main()
{
    bool lowFirst = false; // You choose with this if you want to sort it from lowest to highest or vise versa
    int array[]{2,5,1,6,8,9,12,-5}; // some random array, CHANGABLE
    int lenght = sizeof(array)/sizeof(array[0]);
    if (lowFirst){ // true to so sort if from lowest element to highest
        bubbleSortLow(array, lenght);
    }else{
        bubbleSortHigh(array, lenght);
    }
    print(array,lenght); // some nice print

    return 0;
}

void bubbleSortHigh(int array[],int lenght) // highest element is first
{
    for (int i = 0; i < lenght - 1; i++){
        for (int j = i+1; j < lenght; j++){
            if (array[i] < array[j]){
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
}

void bubbleSortLow(int array[],int lenght) // Lowest element is first
{
    for (int i = 0; i < lenght - 1; i++){
        for (int j = i+1; j < lenght; j++){
            if (array[i] > array[j]){
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
}


void print(int array[],int lenght)
{
    for (int i = 0; i < lenght; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}