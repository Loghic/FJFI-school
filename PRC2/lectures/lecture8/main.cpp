#include <fstream>
#include "iostream"

using namespace std;

const int N = 10;

const char *NAME = "data.txt";

//write to file without exceptions
bool write_to_file(const char* name)
{
    ofstream output(name); // to overwrite file
//    ofstream output(name, std::ios_base::app); // to append the file
    if(!output){
        return false;
    }
    for (int i = 1; i <= N; ++i){
        output << i << " ";
    }

    output << endl;

    output.close();

    return bool(output);
}

void read_from_file(const char* name){
    ifstream input(name);
    //skipping controls
    if (!input){
        cout << "File could not be open!" << endl;
    }

    int i;
    while(input >> i){
        cout << i << endl;
    }
}

int main() {
    if (write_to_file(NAME)){
        cout << "Done!" << endl;
    }else{
        cout << "ERROR!" << endl;
    }
    read_from_file(NAME);
    return 0;
}
