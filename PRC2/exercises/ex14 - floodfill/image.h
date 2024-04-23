#ifndef EX14___FLOODFILL_IMAGE_H
#define EX14___FLOODFILL_IMAGE_H

#include "vector"
#include "string"
#include "fstream"
#include "iostream"

#include "color.h"
#include "imageexception.h"
#include "painter.h"

#include "debug.h"


const int N = 1;

class Painter;


// abstract class
class Image{
    unsigned int width;
    unsigned int height;
    unsigned int oldH = 0;
    unsigned int oldW = 0;
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
        oldW = N;
        oldH = N;
#ifdef DEBUG
        std::cout << "Image: Constructor without parameters\n";
#endif
    }
    Image(std::string path) : height(0), width(0), opened(true), changed(false), fileName(path)
    {
        pixels = new std::vector<Color> (N*N);
        f.open(fileName);
        if (!f.is_open()){

            throw ImageException("Could not open file!");
#ifdef DEBUG
            std::cerr << "Failed to open the file for reading\n";
#endif
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
    void save() { saveToFile(fileName);}
    void close() {
        if (f.is_open()) {
            f.close();
        }
    }
    void paint() {
        if (painter != nullptr) {
            painter->paint(); // Delegate the painting task to the assigned painter
        } else {
            // Default behavior if no painter is set
            std::cout << "Default painting behavior" << std::endl;
        }
    }
    unsigned int getWidth() const {return width;}
    unsigned int getHeight() const {return height;}
    void setWidth(unsigned int width) {
        if (oldW < width){
            delete pixels;
            pixels = new std::vector<Color>;
            for (auto row = 0; row < width; ++row){
                for (auto col = 0; col < height; ++col){
                    pixels->push_back(0);
                }
            }
            oldW = width;
        }
        this->width = width;
    }
    void setHeight(unsigned int height) {
        if (oldH < height){
            delete pixels;
            pixels = new std::vector<Color>;
            for (auto row = 0; row < width; ++row){
                for (auto col = 0; col < height; ++col){
                    pixels->push_back(0);
                }
            }
            oldH = height;
        }
        this->height = height;
    }
    void setPixel(unsigned int x, unsigned int y, Color c) { (*this)(x,y) = c;}
    Color getPixel(unsigned int x, unsigned int y) {return this->operator()(x,y);}
    Color& operator()(unsigned int x, unsigned int y)
    {
        if (x > getWidth() || y > getHeight()){
            throw ImageException("Out of range");
#ifdef DEBUG
        std::cout << "Out of range!\n";
#endif
        }
        return (*pixels)[getHeight() * x + y];
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
    void loadFromFile(std::string path) override;
    void saveToFile(std::string path) override;
    void print()
    {
        for (auto row = 0; row < getHeight(); ++row){
            for (auto col = 0; col < getWidth(); ++col){
                Color pixel = getPixel(col,row);
                if (pixel > 1){
                    std::cout << "\033[31m"; // set text color to red
                    std::cout << pixel << " ";
                    std::cout << "\033[0m"; // reset text color
                }else{
                    std::cout << pixel << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

void PBMImage::loadFromFile(std::string path)
{
    std::fstream f;
    f.open(path);
    if (!f.is_open()){
        throw ImageException("Could not open file!");
#ifdef DEBUG
    std::cerr << "Could not open the file!" << std::endl;
#endif
    }

    std::string s;
    std::string tmp;
    bool headerRead = false;
    bool dimensionsRead = false;
    while (std::getline(f, s)){
        if (s[0] == '#') continue;
        // small 'p' be might be useless
        if (!headerRead && s[0] == 'p' || !headerRead && s[0] == 'P') {
            headerRead = true;
            continue;
        }
        if (!dimensionsRead){
            int dim = 0;
            for (char c : s){
                if (c != ' '){
                    if (c < '0' || c > '9'){
                        break;
                    }
                    dim *= 10;
                    dim += int(c) - int('0');
                }else{
                    setWidth(dim);
                    dim = 0;
                }
            }
            setHeight(dim);
            dimensionsRead = true;
            continue;
        }
        tmp += s;
    }
    f.close();
    int w = 0; // width
    int h = 0; // height


    for (char c : tmp){
        if (c < '0' || c > '9') continue;
        setPixel(w,h, int(c - '0'));
        w++;
        if (w == getWidth()){
            w = 0;
            h++;
        }
    }
#ifdef PRINT
    std::cout << "Dimensions are: " << getWidth() << " " << getHeight() << std::endl;
    for (int row = 0; row < getHeight(); ++row){
        for (int col = 0; col < getWidth(); ++col){
            std::cout << getPixel(col,row) << " ";
        }
        std::cout << std::endl;
    }
#endif
}

void PBMImage::saveToFile(std::string path)
{
    std::fstream f;
    f.open(path, std::ios_base::out);
    if (!f.is_open()){
        throw ImageException("Could not open file!");
#ifdef DEBUG
    std::cout << "Couldn't open the file!\n";
#endif
    }

    f << "P1" << std::endl;
    f << getWidth() << " " << getHeight() << std::endl;
    for (auto row = 0; row < getHeight(); ++row){
        for (auto col = 0; col < getWidth(); ++col){
            f << getPixel(col, row) << " ";
        }
        f << std::endl;
    }

}



#endif //EX14___FLOODFILL_IMAGE_H
