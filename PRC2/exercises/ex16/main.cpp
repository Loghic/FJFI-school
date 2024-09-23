#include <iostream>
#include <exception>

using namespace std;

class arr
{
    int *data;
    int size;

public:
    arr(int *_data, int _size);
    arr(int _size);
    arr(arr &other);
    ~arr();
    arr & operator=(arr &rhs)
    {
        if (this == &rhs){
            return *this;
        }

        delete this->data;
        this->size = rhs.size;
        this->data = new int [this->size];
        return *this;
    }
};

int main(){
    return 0;
}



