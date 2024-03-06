#ifndef EX8___BINARY_LOOKUP_TREE_OF_TYPE_T_COMPLEX_H
#define EX8___BINARY_LOOKUP_TREE_OF_TYPE_T_COMPLEX_H

template<typename T>
class Complex {
    T real;
    T imag;
public:
    Complex(T r, T i) : real(r), imag(i){}
    T getReal() const {return real;}
    T getImag() const {return imag;}
    void setReal(T val);
    void setImag(T val);
};

template<typename T>
void Complex<T>::setReal(T val) //Complex is template so we have to use <T>
{
    this->real = val;
}

template<typename T>
void Complex<T>::setImag(T val)
{
    this->imag = val;
}

#endif //EX8___BINARY_LOOKUP_TREE_OF_TYPE_T_COMPLEX_H
