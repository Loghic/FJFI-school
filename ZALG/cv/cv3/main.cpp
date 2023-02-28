#include <iostream>

using namespace std;

enum {OK};

class myItem
{
    public:
        int key = 0;
        // for now only key, there could be some useful values (names, value etc.)
        myItem *left = nullptr;
        myItem *right = nullptr;
};

myItem *myFind (myItem * top, int myVal)
{
    if (!top){
        return nullptr;
    }

    if (top->key == myVal){
        return top;
    }

    if (top->key > myVal){
        return myFind(top, myVal);
    }else{
        return myFind(top, myVal);
    }

}

myItem *findCycle(myItem *top, int myVal)
{
    myItem *p = top;

    while (p && p->key != myVal){
        if (myVal < p->key){
            p = p->left;
        }else{
            p = p->right;
        }
    }
    return p;
}


int main()
{
    myItem * root = nullptr;
    myItem* a = myFind(root,10);
    myItem* b = findCycle(root,20);
    cout << "Recursion: " << (a ? "Found it" : "Havent found it") << endl;
    cout << "Cycle: " << (b ? "Found it" : "Havent found it") << endl;
    return OK;
}