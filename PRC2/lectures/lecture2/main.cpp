#include <iostream>
using namespace std;

class field
{
    int* data;
    int size;
public:
    explicit field(int size);

};

field::field(int size) : size(size)
{
    data = new int[size];
}

int main() {

}
