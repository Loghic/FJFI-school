#include <iostream>
#include "iomanip"
#include "cmath"


using namespace std;

/*
 * User defined output names
 */
ostream& line(ostream &os){
    os << "__________________";
    return os;
}

// double *F (double); // prototype of function  (returns double * and argument is of type double)

// double (*F) (double) // function pointer

void functionTable(double a, double b, unsigned int steps, double (*F)(double)){
//    (*F)(0) <=> F(x) also possible to omit pointer
    cout << line << endl;
    double step = abs(b-a) / steps;
    double x = a;
    for (int i = 0; i <= steps; i++){
//        cout << setw(10) << setfill('_') << x << " " << (*F)(x) << endl; // only active for x
        cout << setw(10) << setprecision(5) << x << " " << (*F)(x) << endl; // only active for x
        x += step;
    }
    cout << line << endl;
}

int main() {

    functionTable(0, 3.141592, 10, &sin); // one possible declaration
//    functionTable(0, 3.141592, 10, sin); // this also possible
    cout << hex << 255 << endl;
    return 0;
}
