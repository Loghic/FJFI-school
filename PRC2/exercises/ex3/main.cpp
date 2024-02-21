#include <iostream>
#include "fstream"

using namespace std;

void writeToFile()
{
    fstream f;
    // doubling makes it print out as single on
    // or writing R "()" then its raw string and its writing everything
//    cout << R"(D\\work\\test.txt)" << endl;
    f.open("test.txt", ios_base::out); // writing into file (overwrites everything)
//    f.open("test.txt", ios_base::app); // for appending file
    if(!f.is_open()){
        cerr << "Failed to open the file writing!\n";
        return;
    }

    for (auto i = 0; i < 11; i++){
        f << i << endl;
    }
    f.close();
}

void readFromFile()
{
    fstream f;
    f.open(R"(test.txt)", ios_base::in);
//    f.open(R"(test.txt)", ios_base::binary); // to read binary file
    if (!f.is_open()){
        cerr << "Failed to pen te file fo reading\n";
        return;
    }

//    int i;
    // ends as soon as it sees something other than int
//    while (f >> i){ // only possible if we know the type in file
//        cout << i << endl;
//    }

//    string s;
//    while (f >> s){ // reads only 1 word, not whole line
//        cout << s << endl;
//    }
    string s;
    while (getline(f, s)){ // gets whole line
        cout << s << endl;
    }
    f.close();
}

int main() {
//    writeToFile();
    readFromFile();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
