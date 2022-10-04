#include <iostream>
#include "flatterrer.hpp"
#include "flatterrer.cpp"
using namespace std;

int main()
{
    int number, option, ret;
    ret = input(number, option);
    if (ret == 1){
        return 1;
    }
    if (option){
        cout << "Faktorial using while cycle: " << faktorialWhile(number) << endl;
    }else{
        cout << "Faktorial using for cycle: " << faktorialFor(number) << endl;
    }
    faktorial(number, option);
    // flatterring();
    return 0;
}