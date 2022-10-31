#include <iostream>

using namespace std;

struct list{
    int length = 0;
    int index = 0;
    double value = 0;

    void print()
    {
        cout << "Hodnota prvku je: " << value << " a je na pozici: " << index << endl;
    }

};

list findMax(list, double[]);

int main ()
{
    double someList[]{1,2,233,4,5,-2,-3,100};
    list myList;
    myList.length = sizeof(someList)/sizeof(someList[0]);
    myList = findMax(myList, someList);
    myList.print();
    return 0;
}

list findMax(list myList, double myVector[])
{
    myList.value = myVector[0];
    for (int i{0}; i < myList.length; i++){
        if (myVector[i] > myList.value){
            myList.value = myVector[i];
            myList.index = i;
        }
    }
    return myList;
}