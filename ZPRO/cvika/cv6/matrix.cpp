#include <iostream>
using namespace std;

void print(double[][2]);
void matrixMul(double[][2],double[][2],double[][2]);

int main()
{

    double matrix1[2][2]{{5,7},{3,2}};
    double matrix2[2][2]{{5,3},{2,4}};
    double matrix3[2][2]{{}};
    int len1 = sizeof(matrix1)/sizeof(matrix1[0]);
    int len2 = 3;
    print(matrix1);
    cout << "------------------------------------------" << endl;
    print(matrix2);
    cout << "------------------------------------------" << endl;
    matrixMul(matrix1,matrix2,matrix3);
    print(matrix3);
    return 0;
}

void matrixMul(double mat1[][2],double mat2[][2],double mat3[][2])
{
     for (int row = 0; row < 2; row++){
        for (int col = 0; col < 2; col++){
            for (int correction = 0; correction < 2; correction++){
                mat3[row][col] += mat1[row][correction] * mat2[correction][col];
            }
        }
    }
}

void print(double matrix[][2])
{
    for (int i {0}; i < 2; i++){
        for (int j {0}; j < 2; j++){
            cout << "[ " <<  matrix[i][j] << "] ";
        }
        cout << endl;
    }
}
