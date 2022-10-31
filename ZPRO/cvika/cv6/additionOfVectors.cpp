#include <iostream>
using namespace std;

enum {OK, ERROR_INPUT = 100};

void addition(double vector1[], double vector2[], int len1, int len2,double vec3[]);

void print(double[], int);

void printRow(double [], int);


int main()
{
    double vec1[]{2,32,123,5,2,31,5,-23,-5, 2, 1 ,23 , 4 ,53 , 345 , 545324,  4325 ,345};
    double vec2[]{23,12,512,521,5,12,5123,5};
    int len1 = sizeof(vec1)/sizeof(vec1[0]);
    int len2 = sizeof(vec2)/sizeof(vec2[0]);
    if (len1 == 0 && len2 == 0){
        cout << "Both vectors are equal to zero!" << endl;
        return ERROR_INPUT;
    }
    double vec3[max(len1,len2)]{};
    addition(vec1,vec2,len1,len2,vec3);
    print(vec3, max(len1,len2));
    cout << endl;
    printRow(vec3, max(len1,len2));
    return OK;
}

void addition(double vector1[], double vector2[], int len1, int len2,double tmpVector[])
{
    for (int i {0}; i < min(len1,len2); i ++){
        tmpVector[i] = vector1[i] + vector2[i];
    }
    for (int j = min(len1,len2); j < max(len1,len2); j++){
        tmpVector[j] = (len1 > len2 ? vector1[j] : vector2[j]);
    }
}

void print(double vec[], int len)
{
    for (int i {0}; i < len; i++){
        cout << "[" << vec[i] << "] ";
    }
    cout << endl;
}

void printRow(double vec[], int len)
{
    for (int i {0}; i < len; i++){
        cout << "[ " << vec[i] << " ]" << endl;
    }
}
