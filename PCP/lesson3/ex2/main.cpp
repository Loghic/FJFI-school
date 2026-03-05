#include <iostream>

using namespace std;

template<int N, class T>
T scal_mul(T* a, T* b)
{
  T res = 0;
  for (int i = 0; i < N; i++)
  {
     res += a[i] * b[i];
  }
  return res;
}

template<class T>
T scal_mul(T* a, T* b)
{
  return a[0]*b[0] + a[1]*b[1];
}

template<int N, class T>
struct multiplicator
{
  static inline T scal_multip(T* a, T* b)
  {
    return *a * *b + multiplicator<N-1, T>::scal_multip(a+1, b+1);
  }
};

template<class T>
struct multiplicator<1, T>
{
  static inline T scal_multip(T* a, T* b)
  {
    return *a * *b;
  }
};


const int N = 3;
int main()
{
  double A[N]{1, 2, 3};
  double B[N]{1, 1, 1};
  cout << multiplicator<N, double>::scal_multip(A, B) << endl;
}
