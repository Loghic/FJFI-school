#include <iostream>
#include "cstring"

using namespace std;

//int maximum(int num1, int num2)
//{
//    return num1 > num2 ? num1 : num2;
//}
//
//float maximum(float num1, float num2)
//{
//    return num1 > num2 ? num1 : num2;
//}

template <typename T>
T maximum(T num1, T num2)
{
    return num1 > num2 ? num1 : num2;
}

char* maximum(char *a, char *b)
{
    cout << "Template overloading\n";

    //manually
//    int len = strlen(a) > strlen(b) ? strlen(a) : strlen(b);
//    int it = 0;
//    while (len > 0){
//        if (a[it] < b[it]){
//            return a;
//        }else if (a[it] > b[it]){
//            return b;
//        }
//        len--;
//        it++;
//    }

//using library
    return strcmp(a, b) > 0 ? b : a;
}


int main() {
    int a, b;
    float c,d;
    a = 5;
    b = 10;
    c = 3.2;
    d = -5.3;
    char s2[10] = "Salut";
    char s1[10] = "Hello";
//    char s2[10] = "Salut";
    cout << "maximum int: " << maximum(a,b) << endl;
    cout << "maximum float: " << maximum(c,d) << endl;
    cout << "maximum int-float: " << maximum((float) a, d) << endl;
    cout << "maximum float-int: " << maximum( b, (int)c) << endl;

    cout << "maximum float-float in int: " << maximum<int>(c,d) << endl;
    //substitute the int into the T template parameter
    cout << "maximum char: " << maximum(s1,s2) << endl; // T is char*

    return 0;
}
