#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem> // used to check whether output file already exists; c++17

using namespace std;

enum ERRORS{OK, TERMINATION_BY_USER = 10, HELP = 30, ERROR_INPUT = 100, ERROR_UNDEFINED_INPUT,
        ERROR_CANNOT_OPEN_FILE, ERROR_CONVERSION};

enum PARAMETERS{NO_PARAMETERS = 1, NO_INPUT_FILE_NAME = 3, NO_OUTPUT_FILE_NAME, NO_FILE_OVERWRITE_PARAMETER};

enum FILE_OVERWRITE{OVERWRITE_UNDEFINED, NO_OVERWRITE, OVERWRITE};

enum PROGRAM_PARAMETERS{INPUT_PARAMETER = 1, INPUT_FILE_NAME, OUTPUT_FILE_NAME, FILE_OVERWRITE_PARAMETER};


const char HEX_ARR[] = {'0','1','2','3','4','5','6','7',
                    '8','9','a','b','c','d','e','f',};

const char* help = R"ab(Decimal_To_Hex - program for converting whole decimal numbers to Hex numbers
USE: Decimal_To_Hex [parameter1] [input file] [output file] [overwrite file]

Possible parameters:
'-c' or '/c' to input your numbers through command line
'-f' or '/f' to input numbers using file
'-t' or '/t' to terminate program

For existing output file it is possible put parameters:
'-o' or '\o' to overwrite existing file
'-a' or '\a' to append existing file)ab";

const int HEX = 16;

const int BASE = HEX;

const string EMPTY_STRING = string();

void print_help();

void chooseInputType(int argc, char *argv[]);
void inputFromCMDLine();
void inputFromFile(int argc, char *argv[]);
/*
 bool ioFileNames returns true if command line is going to be used for output
                  returns false if output is going to be saved in file
*/
bool ioFileNames(int argc, char *argv[], string &inputFileName, string &outputFileName);
void checkIfOutFileAlreadyExists(string &outputFileName, int overwrite);
//

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
    if (argc == NO_PARAMETERS) {
        cout << "Hello, please "
                "enter '-c' or '/c' to input your numbers through command line \n"
                "enter '-f' or '/f' to input numbers using file \n"
                "enter '-t' or '/t' to terminate program\n";
        cin >> userDecision;
    }else{
        userDecision = argv[INPUT_PARAMETER];
    }

    if ((userDecision.length() != 2) ||  ((userDecision[0] != '-') && (userDecision[0] != '/'))){
        print_help();
        exit(ERROR_UNDEFINED_INPUT);
    }
    switch(userDecision[INPUT_PARAMETER]){
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
    inputFile.open(inputFileName);

    int fileOverwriteSettings = OVERWRITE_UNDEFINED;
    if (argc >= NO_FILE_OVERWRITE_PARAMETER){
        if (argv[FILE_OVERWRITE_PARAMETER][0] == '-' || argv[FILE_OVERWRITE_PARAMETER][0] == '/'){
            if (argv[FILE_OVERWRITE_PARAMETER][1] == 'o' || argv[FILE_OVERWRITE_PARAMETER][1] == 'O'){
                fileOverwriteSettings = OVERWRITE;
            }else if (argv[FILE_OVERWRITE_PARAMETER][1] == 'a' || argv[FILE_OVERWRITE_PARAMETER][1] == 'A')
                fileOverwriteSettings = NO_OVERWRITE;
        }
    }

    if (!toCMDLine) checkIfOutFileAlreadyExists(outputFileName, fileOverwriteSettings);


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
    if (argc < NO_INPUT_FILE_NAME){
        cout << "Please provide the name of input file: ";
        cin >> inputFileName;

    }else inputFileName = argv[INPUT_FILE_NAME];

    if(argc < NO_OUTPUT_FILE_NAME) {
        char answer;
        cout << "Would you like to save hex value to file? y/n\n";
        cin >> answer;
        if (answer == 'y' || answer == 'Y'){
            cout << "Please enter name of output file: ";
            cin >> outputFileName;
            toCMDLine = false;
        }
    }
    else{
        outputFileName = argv[OUTPUT_FILE_NAME];
        toCMDLine = false;
    }
    return toCMDLine; // returns whether the program is going to use cmd line for out
}

void checkIfOutFileAlreadyExists(string &outputFileName, int overwrite)
{
    namespace fs = std::filesystem;
    fs::path f{ outputFileName};
    if (fs::exists(f) && overwrite == OVERWRITE_UNDEFINED){
        cout << outputFileName + " already exists. Would you like to overwrite it? y/n\n";
        char answer;
        cin >> answer;
        if (answer == 'y' || answer == 'Y'){
            ofstream outFile(outputFileName);
            outFile << "";
            outFile.close();
        }
    }else if(overwrite == OVERWRITE){
        ofstream outFile(outputFileName);
        outFile << "";
        outFile.close();
    }
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
