
#include "../../Header_files/GUI/GUIfield.h"

GUIField::GUIField(int pX, int pY) {
    x = pX;
    y = pY;
}

GUIField::~GUIField() {}

int GUIField::getX() {
    return x;
}

int GUIField::getY() {
    return y;
}
