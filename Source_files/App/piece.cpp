#include "../../Header_files/App/piece.h"

Piece::Piece(int pIdPlayer) {
    idPlayer = pIdPlayer;
    type = home;
}
Piece::~Piece(){}

int Piece::getIdPlayer() {
    return idPlayer;
}

Type Piece::getType() {
    return type;
}

int Piece::getPosition() {
    return position;
}

void Piece::setIdPlayer(int pIdPlayer) {
    idPlayer = pIdPlayer;
}

void Piece::setType(Type pType) {
    type = pType;
}

void Piece::setPosition(int pPosition) {
    position = pPosition;
}