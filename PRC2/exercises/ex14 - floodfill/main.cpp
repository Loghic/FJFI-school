#include <iostream>

#include "image.h"
#include "painter.h"

using namespace std;

// 0 is black, 1 is white; for image colors

void floodfill(Image &i, uint sx, uint sy, Color c) // sx, sy - coordinates of seed fill
{
    ; // TODO
}
int main(int argc, char* argv[]) {
    PBMImage i;
//    i.loadFromFile(argv[1]);
    StreamPainter painter(&i);
    painter.setStream(cout);
    i.setPainter(&painter);
//    i.paint();
//    floodfill(i, argv[2], argv[3], argv[4]);
//    i.paint();
//    i.close();
    return 0;
}
