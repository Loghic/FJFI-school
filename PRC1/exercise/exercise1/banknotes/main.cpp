#include <iostream>

using namespace std;
enum {OK};



int main()
{
    int notes [12] = {5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
    int numOfNotes [12] = {};
    int value;
    cout << "Please provide value: " << endl;
    cin >> value;

    for (int i = 0; i < 12; i++){
        int tmp = value / notes[i];
        if (tmp != 0){
            numOfNotes[i] = tmp;
            value = value % notes[i];
        }
    }

    for (int j = 0; j < 12; j++){
        cout << notes[j] << ": " << numOfNotes[j] << endl;
    }
    
    return OK;
}