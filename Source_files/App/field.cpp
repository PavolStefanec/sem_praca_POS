#include "../../Header_files/App/field.h"

Field::Field(Type pType) {
    piece = nullptr;
    type = pType;
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

