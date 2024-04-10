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
    void paint() const {std::cout << "Hello world\n";}
};

#endif //EX14___FLOODFILL_PAINTER_H
