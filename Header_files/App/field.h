#pragma once
#ifndef UNTITLED_FIELD_H
#define UNTITLED_FIELD_H
#include "piece.h"
#include "../consts.h"

//na startField moze byt hracova figurka vzdy len jedna a ostatni hraci toto policko su nuteny vzdy preskocit
class Field {
private:
    Piece* piece;
    Type type;
public:
    Field(Type pType);
    ~Field();
    void setPiece(Piece* pPiece);
    Piece* getPiece();
};
#endif //UNTITLED_FIELD_H
