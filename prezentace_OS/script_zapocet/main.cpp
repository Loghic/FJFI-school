#include "iostream"
#include <fstream>
#include "factorial.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << factorial(5) << endl;

    string line;
    getline(cin, line);

    for (int i = 0; i < stoi(line); ++i){
        if (i%2 == 0){
            cout << "EVEN" << endl;
        }else{
            cout << "ODD" << endl;
        }
    }

    // for more than 1 line in pub*.in
    // while (std::getline(std::cin, line)) {
    //     cout << "Read line: " << line << std::endl;
    // }

    // if (argc < 2){
    //     cout << "Usage: " << argv[0] << " <test_string>" << endl;
    //     return EXIT_FAILURE;
    // }
    // const char* filenameIn = argv[1];
    // fstream fileIn;
    // fileIn.open(filenameIn);

    // if (!fileIn.is_open()) {
    //     cerr << "Error: Unable to open file " << filenameIn << endl;
    //     return EXIT_FAILURE;
    // }
    // string line;
    // getline(fileIn, line);

    // const char* filenameOut = argv[2];
    // fstream fileOut;
    // fileOut.open(filenameOut, ios_base::out);
    // if(!fileOut.is_open()){
    //     cerr << "Error: Unable to open file " << filenameIn << endl;
    //     return EXIT_FAILURE;
    // }

    // for (int i = 1; i <= stoi(line); ++i){
    //     fileOut << "EVEN" << endl;
    // }

    // fileIn.close();
    // fileOut.close();

}
