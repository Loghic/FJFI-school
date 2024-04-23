#ifndef EX14___FLOODFILL_IMAGEEXCEPTION_H
#define EX14___FLOODFILL_IMAGEEXCEPTION_H

#include <exception>
#include "string"

class ImageException : public std::exception{
    std::string message;
public:
    ImageException(std::string msg) : message(msg) {};
    virtual const char* what() const noexcept
    {
        return message.c_str(); // can be accessed with e.what()
    }
};


#endif //EX14___FLOODFILL_IMAGEEXCEPTION_H
