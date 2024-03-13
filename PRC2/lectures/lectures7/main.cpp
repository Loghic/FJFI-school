#include <iostream>

using namespace std;

template<int N>
struct scal_mul
{
    inline double multiplication(double *a, double *b)
    {
        return *a * *b + scal_mul<N -1>::multiplication(a+1, b+1);
    }
};

template<>
struct scal_mul<0>
{
    inline double multiplication(double *a, double *b)
    {
        return *a + *b;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
