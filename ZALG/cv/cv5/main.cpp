#include <iostream>

using namespace std;

enum {OK, ERROR = 100};
// #define N 8 // in C
const int N = 8; // in c++

void play(int*, int, int&);

int main()
{
    int a[N+1]{};
    int cnt = 0;
    for (int i = 0; i <= N; i++){
        a[i] = 0;
    }
    play(a,1, cnt);
    cout << "----------------"<< endl;
    cout << "Number of solutions: " << cnt << endl;
    cout << "DONE" << endl;
    return OK;
}

void play(int *a, int col, int &cnt)
{
    for (int r = 1; r <= N; r++){
        bool ok = true;

        for (int j = 1; j < col; j++){ // could exchange break for (int j = 1; j < col && ok; j++)
            if (a[col-j] == r || a[col - j] == r-j || a[col-j] == r+j){
                ok = false;
                break;
            }
        }

        if (ok){
            a[col] = r;
            if (col < N){
                play(a, col+1, cnt);
            }else{
                cnt++;
                cout << "----------------"<< endl;
                for (int j = 1; j <= N; j++){
                    cout << a[j] << " ";
                }
                cout << endl;
                cout << "----------------"<< endl;
                for (int row = 1; row <= N; row++){
                    for (int myCol = 1; myCol <= N; myCol++){
                        if (a[myCol] == row){
                            cout << "*";
                        }else{
                            cout << "o";
                        }cout << " ";
                    }
                    cout << endl;

                }
            }
        }
    }
}