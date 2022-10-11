#include <iostream>
#include <string.h>

using namespace std;

struct Strings
{
    string str1;
    string str2;
    int lenghtStr1;
    int lenghtStr2;
    int longerStr;
    int shorterStr;
    void print(int compareResult)
    {
        if (compareResult == 1){
            cout << "The first string :'" << str1 << "' is bigger!" << endl;
        }else if (compareResult == -1){
            cout << "The second string: '" << str2 << "' is bigger!" << endl;
        }else{
            cout << "'" << str1 << "' and '" << str2 << "' are equal"<< endl;
        }
    }
    void input()
    {
        cout << "Please enter 1st string: ";
        cin >> str1;
        cout << "Please enter 2nd string: ";
        cin >> str2;
        lenghtStr1 = str1.size();
        lenghtStr2 = str2.size();
        bigger();
    }

    void bigger()
    {
        if (lenghtStr1 > lenghtStr2){
            longerStr = lenghtStr1;
            shorterStr = lenghtStr2;
        }else{
            longerStr = lenghtStr2;
            shorterStr = lenghtStr1;
        }
    }
};

// compare result '1' 1. is bigger, '0' they are equal, '-1' the second is bigger
int compare(Strings);

int main()
{
    Strings str;
    str.input();
    str.print(compare(str));

    return 0;
}

int compare(Strings str)
{
    int ans = 0;
    int decimalPointPosStr1 = str.lenghtStr1;
    int decimalPointPosStr2 = str.lenghtStr2;
    bool isBigger = false;
    for (size_t i{0}; i < str.longerStr; i++){
        if (i < str.shorterStr && !isBigger){
            if (str.str1[i] > str.str2[i]){
                ans = 1;
                isBigger = true;
            }else if (str.str2[i] > str.str1[i]){
                ans = -1;
                isBigger = true;
            }
        }
        if (i < str.lenghtStr1 && str.str1[i] == '.'){
            decimalPointPosStr1 = i;
        }
        if (i < str.lenghtStr2 && str.str2[i] == '.'){
            decimalPointPosStr2 = i;
        }
    }
    if (decimalPointPosStr1 > decimalPointPosStr2){
        ans = 1;
    }else if (decimalPointPosStr2 > decimalPointPosStr1){
        ans = -1; 
    }else{
        if (str.lenghtStr1 > str.lenghtStr2){
            ans = 1;
        }else if (str.lenghtStr2 > str.lenghtStr1){
            ans = -1;
        }
    }
    return ans;
}

