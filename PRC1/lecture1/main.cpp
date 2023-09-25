#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum {OK};

int main()
{
    string line;
    vector<string> read;

    while (getline(cin, line)){
        read.push_back(line);
    }


    sort(read.begin(), read.end());

    for (auto text: read){
        cout << text << endl;
    }

    return OK;
}