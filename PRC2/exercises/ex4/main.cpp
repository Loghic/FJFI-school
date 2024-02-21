#include <iostream>

using namespace std;

const int shift = 'a' - 'A';

string toUpper(string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z'){
            s[i] -= shift;
        }
    }
    return s;
}

int main() {
    string s;
    while(getline(cin, s)){
        cout << toUpper(s) << endl;
    }
    return 0;
}
