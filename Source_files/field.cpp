#include "../Header_files/field.h"

Field::Field() {
    piece = nullptr;
}

Field::~Field() {
    delete piece;
}

void Field::setPiece(Piece *pPiece) {
    piece = pPiece;
}

