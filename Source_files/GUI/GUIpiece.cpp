#include "../../Header_files/GUI/GUIpiece.h"

GUIPiece::GUIPiece(double pX, double pY) {
    x = pX;
    y = pY;
}

GUIPiece::~GUIPiece() {}

double GUIPiece::getX() {
    return x;
}

double GUIPiece::getY() {
    return y;
}

void GUIPiece::setX(double pX) {
    x = pX;
}

void GUIPiece::setY(double pY) {
    y = pY;
}
