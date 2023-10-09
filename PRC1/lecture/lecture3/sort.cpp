#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

typedef bool (*comparator)(string& s1, string& s2);

enum {OK, ERROR = 100};

const char* help = R"aa(SORT - program for sorting files
USE: SORT [parameter] < [input file] > [output file]
Possible parameters:
-n or /n numerical sorting
-l or /l lexicographical sorting
Ferda Mravenec, prace vseho druhu)aa";

bool lexicographical_comparator(string &s1, string &s2)
{
    return s1 < s2;
}

bool numerical_comparator(string &s1, string &s2)
{
    istringstream input1(s1);
    istringstream input2(s2);
    int n1, n2;
    input1 >> n1;
    input2 >> n2;
    return n1 < n2;
}

void print_help()
{
    cerr << help << endl;
    exit(ERROR);
}

comparator analysis_of_command_line(int argc, char* argv[])
{
    if ((argc != 2) || ((argv[1][0] != '/') && (argv[1][0] != '-'))) print_help();

//    if ((argv[1][0] != '/') || (argv[1][0] != '-')) print_help(); ???

    switch(argv[1][1]){
        case 'n':
            return numerical_comparator;
        case 'l':
            return lexicographical_comparator;
        default:
            print_help();
    }
}

int main(int argc, char* argv[])
{
    auto comp = analysis_of_command_line(argc, argv);

    string line;
    vector<string> data;
    while(getline(cin, line)){
        data.push_back(line);
        if (line[0] == '\0') break;
    }

    sort(data.begin(), data.end(), comp);

    for (auto const &s : data){
        cout << s << endl;
    }

    return OK;
}
