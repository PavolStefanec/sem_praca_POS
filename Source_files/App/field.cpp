#include "../../Header_files/App/field.h"

Field::Field(Type pType, int pColor) {
    piece = nullptr;
    type = pType;
    color = pColor;
}

Field::~Field() {
    if (piece != nullptr) {
        delete piece;
    }
}

void Field::setPiece(Piece *pPiece) {
    piece = pPiece;
}

Piece* Field::getPiece() {
    return piece;
}

int Field::getColor() {
    if (piece != nullptr)
        return piece->getColor();
    return color;
}

int Field::getNumber() {
    if (piece != nullptr)
        return piece->getNumberOfPiece()+1;
    return 0;
}

