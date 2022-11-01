#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readfile();
void sort(vector<int>);
void print(vector<int>);

int main()
{
    readfile();
    return 0;
}

void readfile()
{
    vector<int> list;
    ifstream my_file;
    my_file.open("pub1.in");
    string my_line;
    if (my_file.is_open()){
        while (my_file){
            list.clear();
            if (my_file.eof()){
                break;
            }
            getline(my_file,my_line);
            string tmp;
            int i = 0;
            while(true)
            {
                if (my_line[i] == ' ')
                {
                    try
                    {
                        int vec = stoi(tmp);
                        list.push_back(vec);
                    }
                    catch(const std::exception& e)
                    {
                        break;
                    }
                    
                    tmp = "";
                }
                else {
                    tmp = tmp + my_line[i];
                } 
                i++;
                if (my_line[i] == '\0' || my_line[i] == '\n' || my_line[i] == EOF){
                    try
                    {
                        int vec = stoi(tmp);
                        list.push_back(vec);
                    }
                    catch(const std::exception& e)
                    {
                        break;
                    }
                    break;
                }
            }
            sort(list);
        }
    }else{
        cout << "Cannot read the file!" << endl;
    }
}

void sort(vector<int> list)
{
    for (int i = 0; i < list.size()-1; i++){
        for (int j = i; j < list.size(); j++){
            if (list[i] > list [j]){
                swap(list[i],list[j]);
            }
        }
    }
    print(list);
}

void print(vector<int> list)
{
    for (int i = 0; i < list.size(); i++){
        cout << list[i] << ", ";
    }cout << endl;
}
