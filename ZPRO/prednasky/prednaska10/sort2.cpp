#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using p_comperator = bool (*)(string&,string&);

bool lex_comperator(string& s1, string &s2)
{
    return s1 < s2;
}

const char *text_help = 
R"(Filter sort for sorting contents of text files
Usage:
sort2 [choice] : [input_file] > [output_file]
where [choice] is
-n for sorting by value of the first char of string
-l for lexicographic sorting
It's need to input 1 of the choices
)";

[[noreturn]]
void my_help()
{
    cout << text_help << endl;
    exit(0);
}

p_comperator proccess_parametrs(int argc, char* argv[])
{
    if(argc != 2 || argv[1][0] != '-'){
        my_help();
    };
    if(argv[1][1] == 'l'){
        return lex_comperator;
    }
    else{
        my_help();
    }
}

int main(int argc, char* argv[])
{
    string line;
    vector<string> input_data;
    p_comperator comperator = proccess_parametrs(argc, argv);
    while(getline(cin, line) && line.size() > 0){
        input_data.push_back(line);
    }
    sort(input_data.begin(), input_data.end(), comperator);
    for (string r : input_data){
        cout << r << endl;
    }

    return 0;
}