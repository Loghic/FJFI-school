#include <iostream>

using namespace std;

enum {OK, ERROR = 100};

const int N = 8;

int a[N + 1][N + 1]; // array of distances
int fx[N + 1][N + 1]{}; // array of distances
int fy[N + 1][N + 1]{};

void jump(int x, int y, int cnt = 0, int x0 = -1, int y0 = -1);

void my_print();

void my_find (int x, int y);
void my_find2 (int x, int y);

int main()
{
    for (int i = 0; i <= N; i++){
        for (int j = 0; j <= N; j++){
            a[i][j] = -1; // not visited
        }
    }

    for (int k = 2; k <= N -1; k++){
        a[2][k] = -2; // forbidden square
        a[7][k] = 2;
    }


    int x1 = 1; // 
    int y1 = 1; //  
    jump(x1, y1);  // x1 & y1 are starting positions
    my_print();

    // my_find (8, 8);
    cout << "----------------------------" << endl;
    my_find2(8,8);
    cout << "DONE" << endl;
    return OK;
}

// a[x][y]
void jump(int x, int y, int cnt, int x0, int y0)
{
    if ( x >= 1 && y >= 1 && x <= N && y <= N){
        if (a[x][y] == -1 || a[x][y] > cnt){
            a[x][y] = cnt;

            fx[x][y] = x0; // came from x0 to [x][y]
            fy[x][y] = y0; // same with y

            jump (x + 2, y + 1, cnt+1, x, y);
            jump (x + 2, y - 1, cnt+1, x, y);
            jump (x - 2, y + 1, cnt+1, x, y);
            jump (x - 2, y - 1, cnt+1, x, y);

            jump (x + 1, y + 2, cnt+1, x, y);
            jump (x + 1, y - 2, cnt+1, x, y);
            jump (x - 1, y + 2, cnt+1, x, y);
            jump (x - 1, y - 2, cnt+1, x, y);
        }
    }
}

void my_print()
{
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            cout << a[i][j] << " ";
        }cout << endl;
    }
}

void my_find (int x, int y)
{
    while (x > 0 && y > 0){
        cout << x << ", " << y << endl;
        int t = fx[x][y];
        y = fy[x][y];
        x = t;
    }
}

void my_find2 (int x, int y)
{
    if (x > 0 && y > 0){
        my_find(fx[x][y], fy[x][y]);
        cout << x << ", " << y << endl;
    }
}
