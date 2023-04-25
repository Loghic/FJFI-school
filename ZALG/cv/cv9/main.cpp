#include <iostream>

using namespace std;

enum {OK};

void quicksort(int r, int s)
{
    int h = a[(r+s) / 2];
    int i = r;
    int k = s;

    while (i <= k){
        while (a[i] < h) i++;
        while (a[k] > h) k--;
        if (i <= k){
            swap(a[i], a[k]);
            i++;
            k--;
        }
    }

    if (r < k) quicksort(r,k);
    if (i < s) quicksort(i, s);
}

int main()
{
    init();

    return OK;
}