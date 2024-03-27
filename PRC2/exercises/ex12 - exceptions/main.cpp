#include <iostream>
#include "tree.h"

using namespace std;

// new can throw bad alloc

int main() {
    // we have to specify which datatype is the structure going to be
    Tree<int> t;
    // catch works like if - else, the first ones get check first
    try {
        t.insert(15);
        t.insert(25);
        t.insert(10);
        t.insert(30);

        t.remove(42); // is not in the tree => program will crash

        // the block after the exception is not executed
        t.insert(12);
        t.insert(5);
        t.insert(11);
        t.insert(27);
        t.remove(30);
    }
    catch(TreeException &e){ // object created from exception
        cout << "TreeException caught:\n" << e.what() << endl; // displaying msg from object e
    }
    /*
     * catch(bad_alloc &e){
     * cout << "Error during memory allocation happened: " << e.what() << endl;
     */
    // this catch should cover all from standard library
    catch(exception &e){
        cout << "Standard exception has been caught: " << e.what() << endl;
    }

    // this should cover all exception; It is not a good practice to use it, unless we are debugging
    catch(...){
        // putting this one lastly, IFF it is used
        // cover concrete ones first
        cout << "Unknown exception\n";
    }

    t.print();
    cout << (t.contains(30) ? "TRUE" : "FALSE") << endl;
    return 0;
}
