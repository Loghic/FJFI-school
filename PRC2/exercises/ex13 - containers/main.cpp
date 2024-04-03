#include <iostream>
#include <list>
#include <array>
#include <algorithm>

using namespace std;

const int N = 10;

bool comparator(int a, int b){
    return a > b;
}

int main() {
    cout << "Lambda functions: \n";
    //LAMBDA FUNCTIONS
    //starts with empty square brackets
    //Prototype:
//    [](parameters)->return_type{body}(arguments)
    cout << []()->int{return 42;}() << endl;

    cout << [](auto x)->auto{return x*x;}(5) << endl; // squaring numbers using lambda functions

    //naming lambda functions, therefore it may be used multiple times
    auto sum = [](auto a, auto b)->auto{return a+b;};

    cout << sum(3,5) << endl;

    //list from stdlib
    list<int> lst;
    cout << "LIST: " <<endl;
    for (auto i = 1; i <= N; ++i){
        lst.push_back(i);
    }

    //three possible implementations of iterator in standard library list
    for (list<int>::iterator it = lst.begin(); it != lst.end(); ++it){
        cout << *it << ' ';
    }
    cout << "\n";

    for (auto i = lst.begin(); i != lst.end(); ++i){
        cout << *i << ' ';
    }cout << endl;

    for (int &i : lst){
        cout << i << ' ';
    }cout << endl;

    //array
    array<int, N> arr;
    cout << "Array: " << endl;
//    array<int, N> arr{}; // should be initialized before usage

    for (int i = 0; i < arr.size(); ++i){
        arr[i] = i+1;
    }

    // 3 possible ways to iterate
    for(array<int, N>::iterator it = arr.begin(); it != arr.end(); ++it){
        cout << *it << ' ';
    }cout << endl;

    for (auto i : arr){
        cout << i << ' ';
    }cout << endl;

    arr[2] = 5;
    arr[8] = 2;

    cout << "Unsorted array: ";
    auto pos = 0u; // u after zero means: unsigned zero (great to use with auto)
    while (pos < arr.size()){
        cout << arr[pos] << ' ';
        ++pos;
    }cout << endl;

//    //third parameter can be used to implement our own compare function
//    sort(arr.begin(), arr.end(), less<int>()); // ascending build-in library
//    sort(arr.begin(), arr.end(), greater<int>()); //descending build-in library
//    sort(arr.begin(), arr.end()); //less than ( < ) operator will be used

//    //custom comparison using the compare function
//    sort(arr.begin(), arr.end(), comparator);
//    sort(arr.begin(), arr.end(), &comparator); // this might be useful in same cases

//    //using named lambda expression
//    auto my_compare = [](auto i, auto j)->bool{ return i > j; };
//    sort(arr.begin(), arr.end(), my_compare);

    //using lambda expression without a name
    sort(arr.begin(), arr.end(), [](auto i, auto j)->bool{return i > j;});


    cout << "Sorted array: ";
    for (auto i : arr){ // in case we need to change i pass it by reference: for (auto &i : arr)
        cout << i << " ";
    }cout << endl;

    return 0;
}
