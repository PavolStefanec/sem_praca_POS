#include "../Header_files/board.h"
#include "../Header_files/consts.h"
Board::Board() {
    for (int i = 0; i < NUMBER_OF_FIELDS; i++) {
        board[i] = new Piece;
    }
}

Board::~Board() {
    for (int i = 0; i < NUMBER_OF_FIELDS; i++) {
        delete board[i];
    }
}

Piece* Board::getPiece(int index) {
    if (index >= 0 && index < NUMBER_OF_FIELDS) {
        return board[index];
    } else {
        return nullptr;
    }
}


