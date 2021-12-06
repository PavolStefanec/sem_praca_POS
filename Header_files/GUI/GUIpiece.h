#ifndef UNTITLED_GUIPIECE_H
#define UNTITLED_GUIPIECE_H
#include "../consts.h"
class GUIPiece {
private:
    int x;
    int y;
public:
    GUIPiece(int pX, int pY);
    ~GUIPiece();


    double getX();
    double getY();
    void setX(double pX);
    void setY(double pY);
};
#endif //UNTITLED_GUIPIECE_H
