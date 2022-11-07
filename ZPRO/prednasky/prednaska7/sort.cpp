#include <iostream>
#include <string>
#include "list.hpp"

using namespace std;

int main()
{
    list user_input;
    make(user_input);
    string my_line;
    while (getline(cin, my_line)){
        push_back(user_input, my_line);
    }
    my_print(user_input);
    delete_list(user_input);
}