#include "BigInt.h"
#include <fstream>

using namespace std;

const int LLI_MAX_LEN = to_string(LONG_LONG_MAX).length();

enum {OK, TERMINATED_BY_USER = 100, UNKNOWN_INPUT, ERROR_CANNOT_OPEN_FILE};
enum PARAMETERS{NO_INPUT_FILE_NAME = 2};
enum PROGRAM_PARAMETERS{INPUT_FILE_NAME = 1};

void inputCMD(string &input1, string &input2);
void ioFileNames(int argc, char *argv[], string &inputFileName);
void inputFromFile(int argc, char *argv[], string &s1, string &s2);
void chooseYourInput(int argc, char *argv[], string &s1, string &s2);

void print(BigInt num1, BigInt num2);

int main(int argc, char *argv[]) {
    string number1;
    string number2;

    chooseYourInput( argc, argv, number1, number2);

    return OK;
}

void chooseYourInput(int argc, char *argv[], string &s1, string &s2)
{
    char choice;
    if (argc > 1){
        choice = '2';
    }else {
        cout << "To enter input through console press '1'\n"
                "For entering input from file press '2'\n"
                "To terminate program press '3'\n";
        cin >> choice;
    }

    switch (choice) {
        case '1':
            inputCMD(s1, s2);
            break;
        case '2':
            inputFromFile(argc, argv,s1,s2);
            break;
        case '3':
            cerr << "Program terminated by user!" << endl;
            exit(TERMINATED_BY_USER);
        default:
            cerr << "Unknown input!" << endl;
            exit(UNKNOWN_INPUT);
    }
    BigInt number1(s1);
    BigInt number2(s2);
    print(s1, s2);
}

void inputCMD(string &input1, string &input2)
{
    cout << "Please enter first number: ";
    cin >>input1;
    cout << "Please enter second number: ";
    cin >> input2;
}

void inputFromFile(int argc, char *argv[], string &s1, string &s2)
{
    string inputFileName;
    ifstream inputFile;

    ioFileNames(argc, argv, inputFileName);

    inputFile.open(inputFileName);


    if (!(inputFile.is_open())){
        cerr << "Cannot open file!" << endl;
        exit(ERROR_CANNOT_OPEN_FILE);
    }else{
        string fileLine;
        int lineCounter = 1;
        while (inputFile && lineCounter < 3){
            if(inputFile.eof()){
                break;
            }
            if (lineCounter % 2 == 1){
                getline(inputFile, s1);
            }else if(lineCounter % 2 == 0){
                getline(inputFile, s2);
            }
            lineCounter++;
        }
    }
    inputFile.close();
}

void ioFileNames(int argc, char *argv[], string &inputFileName)
{
    if (argc < NO_INPUT_FILE_NAME){
        cout << "Please provide the name of input file: ";
        cin >> inputFileName;

    }else inputFileName = argv[INPUT_FILE_NAME];
}

void print(BigInt num1, BigInt num2)
{
    if (num1.to_string().size() >= 1 && num1.to_string().size() < LLI_MAX_LEN &&
        num2.to_string().size() >= 1 && num2.to_string().size() < LLI_MAX_LEN){
        long long int number1 = stoll(num1.to_string());
        long long int number2 = stoll(num2.to_string());
        cout << "Print with tests:\n";
        cout << "\nAddition: \n";
        cout << "Calculated number by calculator.h: ";
        cout << num1 + num2 << endl;
        cout << "Number should be: ";
        cout << number1 + number2 << endl;
        cout << endl;

        cout << "Subtraction: \n";
        cout << "Calculated number by calculator.h: ";
        cout << num1 - num2 << endl;
        cout << "Number should be: ";
        cout << number1 - number2 << endl;
        cout << endl;

        cout << "Multiplication: \n";
        cout << "Calculated number by calculator.h: ";
        cout << num1 * num2 << endl;
        if (num1.to_string().size() + num2.to_string().size() < LLI_MAX_LEN){
            cout << "Number should be: ";
            cout << number1 * number2 << endl;
        }
        cout << endl;

        cout << "Division: \n";
        cout << "Calculated number by calculator.h: ";
        cout << num1 / num2 << endl;
        cout << "Number should be: ";
        cout << number1 / number2 << endl;
        cout << endl;
    }else {
        cout << "\nAddition: \n";
        cout << num1 + num2 << endl;
        cout << endl;

        cout << "Subtraction: \n";
        cout << num1 - num2 << endl;
        cout << endl;

        cout << "Multiplication: \n";
        cout << num1 * num2 << endl;
        cout << endl;

        cout << "Division: \n";
        cout << num1 / num2 << endl;
        cout << endl;
    }
}
