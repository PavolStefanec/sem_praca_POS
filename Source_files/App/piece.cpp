#include "../../Header_files/App/piece.h"

Piece::Piece(int pIdPlayer, int pStartFieldPosition) {
    position = -1;
    idPlayer = pIdPlayer;
    startFieldPosition = pStartFieldPosition;
    type = none;
    goEndFieldPosition = pStartFieldPosition == 0 ? NUMBER_OF_GANE_FIELDS - 1 : pStartFieldPosition - 1;
}
Piece::~Piece(){}

int Piece::getIdPlayer() {
    return idPlayer;
}

Type Piece::getType() {
    return type;
}

int Piece::getStartFieldPosition() {
    return startFieldPosition;
}

int Piece::getGoEndFieldPosition() {
    return goEndFieldPosition;
}

int Piece::getPosition() {
    return position;
}

void Piece::setType(Type pType) {
    type = pType;
}

void Piece::setPosition(int pPosition) {
    position = pPosition;
}

