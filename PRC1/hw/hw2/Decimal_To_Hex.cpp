#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

enum {OK, TERMINATION_BY_USER = 10, HELP = 30, ERROR_INPUT = 100, ERROR_UNDEFINED_INPUT,
        ERROR_CANNOT_OPEN_FILE, ERROR_CONVERSION};

const char HEX_ARR[] = {'0','1','2','3','4','5','6','7',
                    '8','9','a','b','c','d','e','f',};

const char* help = R"ab(Decimal_To_Hex - program for converting whole decimal numbers to Hex numbers
USE: Decimal_To_Hex [parameter] > [input file] < [output file]
Possible parameters:
1 input through command line.
2 input using file )ab";

const int BASE = 16;

const int NO_INPUT_FILE_NAME = 2;
const int NO_OUTPUT_FILE_NAME = 4;

const string EMPTY_STRING = string();

void print_help();
void chooseInputType(int argc, char *argv[]);
void inputFromCMDLine();
void inputFromFile(int argc, char *argv[]);
/*
 bool ioFileNames returns true if command line is going to be used for output
                  returns false if output is going to be saved in file
*/
bool ioFileNames(int argc, char *argv[], string &inputFileName, string &outPutFileName);
void calculate(int input, bool toCMDLine = true, string outFileName = EMPTY_STRING);
void print(vector<int> &printedVector, int control, bool controlON = true);
void writeToFile(vector<int> &fileData, string outFileName);

int main(int argc, char *argv[]) {
    chooseInputType(argc, argv);

    return OK;
}

void print_help()
{
    cerr << help << endl;
    exit(HELP);
}

void chooseInputType(int argc, char *argv[])
{
    string userDecision;
    if (argc == 1) {
        cout << "Hello, please enter '-c' or '/c' to input your numbers through command line \n"
                "Press '-f' or '/f' to input numbers using file \n"
                "Press '-t' or '/t' to terminate program\n";
        cin >> userDecision;
    }else{
        userDecision = argv[1];
    }

    if ((userDecision.length() != 2) ||  ((userDecision[0] != '-') && (userDecision[0] != '/'))){
        print_help();
        exit(ERROR_UNDEFINED_INPUT);
    }
    switch(userDecision[1]){
        case 'c':
        case 'C':
            inputFromCMDLine();
            break;
        case 'F':
        case 'f':
            inputFromFile(argc, argv);
            break;
        case 't':
        case 'T':
            cout << "Program has been terminated!" << endl;
            exit(TERMINATION_BY_USER);
        default:
            print_help();
            exit(ERROR_UNDEFINED_INPUT);
    }

}

void inputFromCMDLine()
{
    int input = 0;
    cout << "Please provide whole number: ";
    if(!(cin >> input)){
        cerr << "Input is not a number!" << endl;
        exit(ERROR_INPUT);
    }
    calculate(input);

}

void inputFromFile(int argc, char *argv[])
{
    string inputFileName, outputFileName;
    ifstream inputFile;
    bool toCMDLine = ioFileNames(argc, argv, inputFileName, outputFileName);
//    if (argc == NO_INPUT_FILE_NAME) {
//        cout << "Please provide the name of input file: ";
//        cin >> inputFileName;
//        inputFile.open(inputFileName);
//    }else inputFile.open(argv[2]);
//
//    if(argc == NO_OUTPUT_FILE_NAME) {
//        outputFileName = argv[3];
//        toCMDLine = false;
//    }
//    else{
//        char answer;
//        cout << "Would you like to save hex value to file? y/n\n";
//        cin >> answer;
//        if (answer == 'y'){
//            cout << "Please enter name of output file: ";
//            cin >> outputFileName;
//            toCMDLine = false;
//        }
//    }
    inputFile.open(inputFileName);

    if (!toCMDLine)
    {
        ofstream outFile(outputFileName);
        outFile << "";
        outFile.close();
    }

    if (!(inputFile.is_open())){
        cerr << "Cannot open file!" << endl;
        exit(ERROR_CANNOT_OPEN_FILE);
    }else{
        string fileLine;
        int lineCounter = 1;
        while (inputFile){
            if(inputFile.eof()){
                break;
            }
            getline(inputFile, fileLine);
            try{
                int functionInput = stoi(fileLine);
                if (toCMDLine) calculate(functionInput);
                else calculate(functionInput, toCMDLine, outputFileName);
            }catch(const std::exception& e){
                cerr << "Failed to convert line " << lineCounter << " to int!\n";
                exit(ERROR_CONVERSION);
            }
            lineCounter++;
        }
    }
    inputFile.close();
}

bool ioFileNames(int argc, char *argv[], string &inputFileName, string &outputFileName)
{
    bool toCMDLine = true;
    if (argc == NO_INPUT_FILE_NAME) {
        cout << "Please provide the name of input file: ";
        cin >> inputFileName;

    }else inputFileName = argv[2];

    if(argc == NO_OUTPUT_FILE_NAME) {
        outputFileName = argv[3];
        toCMDLine = false;
    }
    else{
        char answer;
        cout << "Would you like to save hex value to file? y/n\n";
        cin >> answer;
        if (answer == 'y'){
            cout << "Please enter name of output file: ";
            cin >> outputFileName;
            toCMDLine = false;
        }
    }
    return toCMDLine; // returns whether the program is going to use cmd line for out
}

void calculate(int input, bool toCMDLine, string outFileName)
{
    vector<int> numberInNewBase;
    int tmp = input;
    while (tmp >= BASE)
    {
        numberInNewBase.push_back(tmp % BASE);
        tmp /= BASE;
    }
    numberInNewBase.push_back(tmp % BASE);
    reverse(numberInNewBase.begin(), numberInNewBase.end());

    if(toCMDLine)print(numberInNewBase, input);
    else writeToFile(numberInNewBase, outFileName);
}

void print(vector<int> &printedVector, int control, bool controlON) {
    cout << "Number in base " << BASE << " is: ";
    for (int i: printedVector) {
        cout << HEX_ARR[i];
    }
    cout << '\n';
    if (controlON) cout << "Control in hex is: " << hex << control << '\n';
}

void writeToFile(vector<int> &fileData, string outFileName)
{
    string fileLine = "";
    for (int i : fileData){
        fileLine.push_back(HEX_ARR[i]);
    }
    fileLine.push_back('\n');
    ofstream outFile(outFileName,std::ios_base::app);
    if (outFile.is_open()){
        outFile << fileLine;
    }else{
        cerr << "Couldn't open output file!" << endl;
        exit(ERROR_CANNOT_OPEN_FILE);
    }

    outFile.close();
}
