#include <iostream>
#include "utility"
#include "stdexcept" // it should include exception as well
//#include "exception"

#include "initializer_list"

//using namespace std;

class field
{
    int* data;
    int size;
public:
    explicit field(int size);
    field(field &s);
    field(field&& q) : field(q.size) // && R value
    {
        size = q.size;
        std::swap(data, q.data);
    }

    field(std::initializer_list<int> numbers)
    {
        size = numbers.size();
        data = new int[size];
        auto it = numbers.begin(); // doesnt support [], we have to use iterator
        for (int i = 0; i < size; i++){
            data[i] = *it;
            it++;
        }
    }

    ~field() {delete[] data;}
    field& operator=(const field& f);
    field& operator=(field&& f); // && - R value
    field& operator=(int n)
    {
        data[0] = n;
        return *this;
    }
    int& operator[](int n); // for none const declaration of this class
    int operator[](int n) const; // for const declaration of this class
    // Scalar multiplication
    int operator()(const field& f) const; // name of the operator function is: operator()

    void print() const;
};

class x {public: void vypis() {}};

class iterator
{
    x *pointer;
public:
    x* operator->(){return pointer;}
};

field::field(field &s) : size(s.size)
{
    data = new int[size];
    for (int i = 0; i < size; i++){
        data[i] = s.data[i];
    }
}

field::field(int size) : size(size)
{
    data = new int[size];
}

field& field::operator=(const field &f)
{
    if (size != f.size){
        delete[] data;
        data = new int[f.size];
        size = f.size;
    }

    for (int i = 0; i < size; i++){
        data[i] = f.data[i];
    }
    return *this;
}

field& field::operator=(field &&f)
{
    std::swap(data, f.data);
    return *this;
}

int& field::operator[](int n)
{
    if ((n < 1) || (n > size)){ // condition to index array from 1 to n;
        throw std::out_of_range("Index pole mimo meze");
    }

    return data[n-1];
}

int field::operator[](int n) const
{
    if ((n < 1) || (n > size)){ // condition to index array from 1 to n;
        throw std::out_of_range("Index pole mimo meze");
    }

    return data[n-1];
}

void field::print() const
{
  for (int i = 0; i < size; i++){
      std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

int field::operator()(const field& f) const
{
    if (size != f.size){
        throw std::invalid_argument("Pole nemaji stejnou velikost");
    }
    int result = 0;
    for (int i = 0; i < size; i++){
        result += data[i] * f.data[i];
    }
    return result;
}

class numero
{
    int value;
public:
    numero(int value): value(value){}
    explicit operator int(){return value;}

};

//void zpracuj(numero n)
//{
//    // ...
//}

void zpracuj1(int n)
{

}

int main()
{
    field p{1,1,1,1};
    p[1] = 8;
    p.print();
//    field q(4);
    const field q{1,1,1,1};
    q.print();
//    q = p;
//    q = std::move(p);
//    field r = p+q;
//    q[0] = 3;
    std::cout << q[1] << std::endl;
    q.print();
    std::cout << q(p) << std::endl;


    numero n1(8);
    zpracuj1((int)n1);
    zpracuj1(9);


    iterator it;
    it->vypis();
    return 0;
}
