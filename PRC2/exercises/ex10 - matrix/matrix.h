#ifndef EX10_MATRIX_MATRIX_H
#define EX10_MATRIX_MATRIX_H

#include "iostream"

#include "iomanip" // setw() is part of it

using namespace std;

//const bool DEBUG = false; // one approach how to debug program by adding it to prints
#include "debug.h" // another using by #ifdef
//using it as include means we occupy memory with prints, that didn't show and the variables used for debugging

//template<typename T = float, unsigned int N = 3>
template<typename T, unsigned int N>
class Matrix{
    T *data;
public:
    Matrix() : data(new T[N*N])
    {
        #ifdef DEBUG
            cout << "Constructor without parameters\n";
        #endif
    }
    Matrix(T offDiag, T diag); // constructor with param
    Matrix(const Matrix<T,N> &other); //copy constructor
    Matrix(Matrix<T,N> &&other); //move constructor
    ~Matrix(); // destructor
    Matrix<T,N>& operator=(const Matrix<T,N> &rhs); //copy ... (rhs = right hand side)
    Matrix<T,N>& operator=(Matrix<T,N> &&rhs); //move
    T& operator()(unsigned int row, unsigned int column); // indexing of matrix eg. m(5,3);
};

template<typename T, unsigned int N>
Matrix<T,N>::Matrix(T offDiag, T diag)
    : data(new T[N*N])
{
//    if (DEBUG){
//        cout << "Constructor\n";
//    }

    #ifdef DEBUG
        cout << "Constructor\n";
    #endif
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < N; j++){
            (*this)(i,j) = (i == j ? diag : offDiag); // usage of operator()
//            this->operator()(i,j) = (i == j ? diag : offDiag); // same as the example above
        }
    }

}

template<typename T, unsigned int N>
Matrix<T,N>::Matrix(const Matrix<T, N> &other)
    : data(new T[N*N])
{
    #ifdef DEBUG
        cout << "Copy constructor\n";
    #endif
    for (auto i = 0; i < N*N; i++){
        this->data[i] = other.data[i];
    }
}


//move constructor
template<typename T, unsigned int N>
Matrix<T,N>::Matrix(Matrix<T, N> &&other)
    : data(other.data)
{
    other.data = nullptr;
}

template<typename T, unsigned int N>
Matrix<T,N>::~Matrix()
{
    #ifdef DEBUG
        cout << "Destructor!\n";
    #endif
    if (data) {
        delete [] data;
    }
    data = nullptr;
}

template<typename T, unsigned int N>
Matrix<T,N>& Matrix<T,N>::operator=(const Matrix<T,N> &rhs)
{
#ifdef DEBUG
    cout << "Assignment OP\n";
#endif
    //lhs and rhs are the same
    if (this == &rhs){
        return *this;
    }
    for(auto i = 0; i < N*N; i++){
        this->data[i] = rhs.data[i];
    }
    return *this;
}

//move
template<typename T, unsigned int N>
Matrix<T,N>& Matrix<T,N>::operator=(Matrix<T,N> &&rhs)
{
#ifdef DEBUG
    cout << "Move OP\n";
#endif
    if (this == &rhs){
        return *this;
    }
    //prevent memory leak
    if (this->data){
        delete [] this->data;
    }
    this->data = rhs.data; // shallow copy
    rhs.data = nullptr;; // stealing
    return *this;
}

template<typename T, unsigned int N>
T& Matrix<T, N>::operator()(unsigned int row, unsigned int column)
{
    if(row >= N || column >= N){
        throw out_of_range("Index outside of matrix");
    }
    return this->data[N*row + column];
}



//declaration of this in function is not needed
template<typename T, unsigned int N>
ostream& operator<<(ostream& os, Matrix<T,N> &m) // overloading of output stream operator
{
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < N; j++){
            os << setw(10) << setprecision(8) << m(i,j);
        }
        os << endl; // after the end of row
    }
    return os;
}

// addition of two matrix together
template<typename T, unsigned int N>
Matrix<T,N> operator+(Matrix<T,N>&a, Matrix<T,N>&b) // overloading of + operator
{
    Matrix<T,N> c;
    for (auto i = 0; i < N; i ++){
        for (auto j = 0; j < N; j++){
            c(i,j) = a(i,j) + b(i,j);
        }
    }
    return c;
}

#endif //EX10_MATRIX_MATRIX_H
