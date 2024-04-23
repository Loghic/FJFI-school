#include <iostream>

#include "iomanip"

#include "image.h"
#include "painter.h"

using namespace std;

// 0 is black, 1 is white; for image colors

void floodfillExecute(Image &i, uint sx, uint sy, Color c, Color initialColor);

void floodfill(Image &i, uint sx, uint sy, Color c)
{
    Color initialColor = i.getPixel(sx,sy);
    floodfillExecute(i, sx, sy, c, initialColor);
}

void floodfillExecute(Image &i, uint sx, uint sy, Color c, Color initialColor) // sx, sy - coordinates of seed fill
{
    if (i.getPixel(sx, sy) == c){
        return;
    }
    if (sx >= 0 && sx < i.getWidth() && sy >= 0 && sy < i.getHeight()){
        uint direction[8][2];
        for (int it = 0; it < 8; ++it){
            if (it >= 2){
                if (it % 2 == 0){
                    direction[it][0] = sx + 1;
                }else {
                    direction[it][0] = sx - 1;
                }
                switch (it) {
                    case 4:
                    case 5:
                        direction[it][1] = sy + 1;
                        break;
                    case 6:
                    case 7:
                        direction[it][1] = sy -1;
                        break;
                    default:
                        direction[it][1] = sy;
                }
            }else{
                direction[it][0] = sx;
                if (it % 2 == 0){
                    direction[it][1] = sy + 1;
                }else{
                    direction[it][1] = sy - 1;
                }
            }
        }

        // four directions (up, down, right, left)
        i.setPixel(sx, sy, c);
        for (int pos = 0; pos < 4; ++pos){
            uint posX = direction[pos][0];
            uint posY = direction[pos][1];

            if (posX > i.getWidth() || posY > i.getHeight()){
                continue;
            }else if (i.getPixel(posX, posY) == initialColor){
                floodfillExecute(i, direction[pos][0], direction[pos][1], c, initialColor);
            }
        }
    }
}
int main(int argc, char* argv[]) {
    PBMImage i;
    i.loadFromFile("maze.pbm");
    StreamPainter painter(&i);
    painter.setStream(cout);
    i.setPainter(&painter);


    floodfill(i, 0, 0, 3);

    cout << setw(i.getWidth()) << setfill('-') << "-" << endl;
    i.print();
    i.saveToFile("lennaOut.pbm");
    i.close();

//    PBMImage i;
//    i.loadFromFile(argv[1]);
//    StreamPainter painter(&i);
//    painter.setStream(cout);
//    i.setPainter(&painter);
//    i.paint();
//    floodfill(i, argv[2], argv[3], argv[4]);
//    i.paint();
//    i.close();

    return 0;
}
