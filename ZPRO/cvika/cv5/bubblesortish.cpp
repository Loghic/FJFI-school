#include <iostream>
using namespace std;

void bubbleSortHigh(int[],int);
void bubbleSortLow(int[],int);
void print(int[],int);

int main()
{
    bool lowFirst = false;
    int array[]{2,5,1,6,8,9,12,-5};
    int lenght = sizeof(array)/sizeof(array[0]);
    if (lowFirst){
        bubbleSortLow(array, lenght);
    }else{
        bubbleSortHigh(array, lenght);
    }
    print(array,lenght);

    return 0;
}

void bubbleSortHigh(int array[],int lenght)
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

void bubbleSortLow(int array[],int lenght)
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