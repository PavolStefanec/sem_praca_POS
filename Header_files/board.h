#pragma once
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