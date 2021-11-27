#include "../Header_files/piece.h"

Piece::Piece() {
    isHome = true;
}
Piece::~Piece(){}

bool Piece::getIsHome() {
    return isHome;
}

void Piece::setIsHome(bool pIsHome) {
    isHome = pIsHome;
}

