#ifndef EX14___FLOODFILL_PAINTER_H
#define EX14___FLOODFILL_PAINTER_H

#include "ostream"

class Image;

// abstract class
class Painter{
protected:
    Image *image;
public:
    Painter(Image *img) : image(img)
    {
#ifdef DEBUG
        std::cout << "Painter: Constructor with parameter\n";
#endif
    }
    virtual ~Painter()
    {
#ifdef DEBUG
        std::cout << "Painter: Destructor\n";
#endif
    }
    virtual void paint() const {std::cout << "Hello Painter\n";} // pure virtual
};

class StreamPainter : public Painter{
protected:
    std::ostream* canvas;
public:
    StreamPainter(Image *img) : Painter(img)
    {
#ifdef DEBUG
        std::cout << "StreamPainter: Constructor with parameter\n";
#endif
    }
    void setStream(std::ostream &os) {canvas = &os;}
    virtual ~StreamPainter() {}
    void paint() const {
        static int calls;
        if (calls % 2 == 0){
            (*canvas) << "\033[31m"; // set text color to red
        }else{
            (*canvas) << "\033[0m"; // reset text color
        }
        calls++;
//        (*canvas) << "\033[31m"; // set text color to red
//        (*canvas) << "Helloo" << std::endl;
//        (*canvas) << "\033[0m"; // reset text color
    }
};

#endif //EX14___FLOODFILL_PAINTER_H
