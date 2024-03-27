#ifndef EX12___EXCEPTIONS_TREEEXCEPTION_H
#define EX12___EXCEPTIONS_TREEEXCEPTION_H

#include "exception"
#include "string"

using namespace std;


// using this link: https://cplusplus.com/reference/exception/exception/

//specialization of exception
class TreeException : public exception{ //exception is part of std
    string message;
public:
    TreeException(string msg) : message(msg) {;}
    virtual const char* what() const noexcept{
       // we have to convert string to char*
        return message.c_str(); // constant char*
//        return message.data(); // non-constant char *
    }
};

#endif //EX12___EXCEPTIONS_TREEEXCEPTION_H
