#pragma once
#ifndef UNTITLED_BOARD_H
#define UNTITLED_BOARD_H
#include "piece.h"
#include "consts.h"

class Board {
private:
    Piece* board[NUMBER_OF_FIELDS];
public:
    Board();
    ~Board();
    Piece* getPiece(int index);
};
#endif //UNTITLED_BOARD_H
