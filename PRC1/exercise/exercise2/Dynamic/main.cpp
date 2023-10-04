#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum {OK,ERROR=100};

const int MAX_MOD = 100;
const int MAX = 100;
const int MIN = 1;

//1. Nechte uzivatele zadat pozadovany pocet nahodnych cisel mezi 1 a 100
//2. Dynamicky alokujte pole pozadovane velikosit
//3. pole naplnte nahodnymi cisly mezi 1 a 100 (pouzijte funkci rand)
//4. pole vytisknete
//5. najdete v poli nejmensi prvek
//6. uvolnete pamet

//T *ptr = new T[N];
//ptr[0] = t0;
//delete []ptr;

int input();
void fillArr(int *arr, unsigned int N);
void printArr(int *arr, unsigned int N);
int findSmallestElement(int *arr, unsigned int N);

int main() {
    int num = input();
    int *ptrArr = new int[num];
    srand(time(nullptr));

    fillArr(ptrArr, num);
    printArr(ptrArr, num);

    int sEl = findSmallestElement(ptrArr, num);
    cout << "Smallest element in array is: " << sEl << endl;

    delete []ptrArr;
    ptrArr = nullptr;

    printArr(ptrArr, num);

    return OK;
}

int input()
{
    int num;
    cout << "Hello, how many random numbers between 1 and 100 do you need? ";
    cin >> num;
    if (num > MAX || num < MIN){
        if (num == 0){
            cout << "Input has to be a number or not equal to zero!" << endl;
        }else {
            cout << "Number is too big or too small!" << endl;
        }
        exit(ERROR);
    }
    return num;

}

void fillArr(int *arr, unsigned int N)
{
    for (unsigned int i =0; i < N; i++){
        arr[i] = rand () % MAX_MOD+1;
    }
}

void printArr(int *arr, unsigned int N)
{
    for (unsigned int i =0; i < N; i++){
        cout << "Arr[" << i << "]: " << arr[i] << endl;
        }
}

int findSmallestElement(int *arr, unsigned int N)
{
    int smallestElement = arr[0];
    for (unsigned int i =1; i < N; i++){
        if (arr[i] < smallestElement){
            smallestElement = arr[i];
        }
    }
    return smallestElement;
}
