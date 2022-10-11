#include <iostream>
#include <string.h>

using namespace std;

int compare(const char*, const char*, const int, const int);

int main()
{
    const char* x = "122.22";
    const char* y = "130";
    int lenghtX = strlen(x);
    int lenghtY = strlen(y);
    int cmpRes = compare(x,y,lenghtX,lenghtY); // compare result '1' 1. is bigger, '0' they are equal, '-1' the second is bigger
    if (cmpRes == 1){
        cout << "The first string is bigger!" << endl;
    }else if (cmpRes == -1){
        cout << "Second string is bigger!" << endl;
    }else{
        cout << "They are equal!" << endl;
    }
    return 0;
}

int compare(const char* x, const char* y, const int lenghtX, const int lenghtY)
{
    int ans = 0;
    int posPointX = 0;
    int posPointY = 0;
    bool isBigger = false;
    for (size_t i{0}; i < lenghtX && i < lenghtY; i++){
        if (!isBigger){
            if (x[i] > y[i]){
                ans = 1;
                isBigger = true;
            }else if (y[i] > x[i]){
                ans = -1;
                isBigger = true;
            }
        }
        if (x[i] == '.'){
            posPointX = i;
        }
        if (y[i] == '.'){
            posPointY = i;
        }
    }
    if (posPointX > posPointY){
        ans = -1;
    }else if (posPointY > posPointX){
        ans = 1; 
    }else{
        if (lenghtX > lenghtY){
            ans = 1;
        }else if (lenghtY > lenghtX){
            ans = -1;
        }
    }
    return ans;
}
