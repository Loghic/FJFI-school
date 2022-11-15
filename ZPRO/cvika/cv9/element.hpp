#ifndef __element_HPP__
#define __element_HPP__



typedef int Data;

// element of oneway listed
// bothway list -> element* previous;
struct element{
    Data data;
    element* next;
};

#endif // __element_HPP__