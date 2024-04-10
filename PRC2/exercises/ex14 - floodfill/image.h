#ifndef EX14___FLOODFILL_IMAGE_H
#define EX14___FLOODFILL_IMAGE_H

#include "vector"
#include "string"
#include "fstream"

#include "color.h"
#include "imageexception.h"

#include "debug.h"


const int N = 100;

class Painter;


// abstract class
class Image{
    unsigned int width;
    unsigned int height;
    std::vector<Color> *pixels;
    std::string fileName;
    std::fstream f;
    bool opened;
    bool changed;
    Painter *painter;
public:
    Image() : height(N), width(N), changed(false), opened(false)
    {
        pixels = new std::vector<Color>( getHeight()*getWidth() );
        for (auto i = 0; i < getWidth()*getHeight(); ++i){
            pixels->push_back(0); // creates black image
        }
#ifdef DEBUG
        std::cout << "Image: Constructor without parameters\n";
#endif
    }
    Image(std::string path) : height(0), width(0), opened(true), changed(false), fileName(path)
    {
        pixels = new std::vector<Color> (N*N);
        f.open(fileName);
        if (!f.is_open()){

            // TODO exception
            std::cerr << "Failed to open the file for reading\n";
            return;
        }
        std::string s;
        int lineCnt = 0;
        while (getline(f, s)){ // gets whole line
            for (char c : s){
                pixels->push_back((int)(c));
            }
        }

#ifdef DEBUG
        std::cout << "Image: Constructor with parameter\n";
#endif
    }
    void setPainter(Painter *p) {painter = p;}
    virtual ~Image()
    {
        delete pixels;
#ifdef DEBUG
        std::cout << "Image: Destructor\n";
#endif
    }
    virtual void loadFromFile(std::string path)  = 0; // = 0 pure virtual
    virtual void saveToFile(std::string path) = 0;
    void save();
    void close() {
        if (f.is_open()) {
            f.close();
        }
    }
    void paint();
    unsigned int getWidth() const {return width;}
    unsigned int getHeight() const {return height;}
    void setPixel(unsigned int x, unsigned int y, Color c) { (*this)(x,y) = c;}
    Color getPixel(unsigned int x, unsigned int y) {return this->operator()(x,y);}
    Color& operator()(unsigned int x, unsigned int y)
    {
        if (x >= getWidth() || y >= getHeight()){
            // TODO exception
        }
        return reinterpret_cast<Color &>(pixels[x + y * getHeight()]);
    }
};

class PBMImage : public Image{
public:
    ~PBMImage()
    {
#ifdef DEBUG
        std::cout << "PBMImage: Destructor\n";
#endif
    }
    void loadFromFile(std::string path) override {;}
    void saveToFile(std::string path) override {;}
};


#endif //EX14___FLOODFILL_IMAGE_H
