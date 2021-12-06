#pragma once
#ifndef UNTITLED_FIELD_H
#define UNTITLED_FIELD_H
#include "piece.h"

class Field {
private:
    Piece* piece;
public:
    Field();
    ~Field();
    void setPiece(Piece* pPiece);
};
#endif //UNTITLED_FIELD_H
