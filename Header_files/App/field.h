#pragma once
#ifndef UNTITLED_FIELD_H
#define UNTITLED_FIELD_H
#include "piece.h"
#include "../consts.h"

//na startField moze byt hracova figurka vzdy len jedna a neplati cik cik domcek
class Field {
private:
    Piece* piece;
    Type type;
    int color;
public:
    Field(Type pType, int pColor);
    ~Field();
    void setPiece(Piece* pPiece);
    Piece* getPiece();
    int getColor();
    int getNumber();
};
#endif //UNTITLED_FIELD_H
