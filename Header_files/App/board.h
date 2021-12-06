#pragma once
#ifndef UNTITLED_BOARD_H
#define UNTITLED_BOARD_H
#include "field.h"
#include "piece.h"
#include "../consts.h"

class Board {
private:
    int numberOfPlayers;
    Field* homeFields[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_MAX_PLAYERS];
    Field* endFields[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_MAX_PLAYERS];
    Field* normalFields[NUMBER_OF_GANE_FIELDS];

    //functions

    Piece* getRemovedPieceNormal(int position);
    void setPieceNormal(Piece* piece, int position);
public:
    Board(int numberOfPlayer);
    ~Board();

    Piece* setNormal(Piece* piece, int position);
    void setHome(Piece* piece);
    void setPieceHome(Piece* piece, int position);
    void setEnd(Piece* piece, int position);

    bool equalsIdPlayerStart(Piece* piece);
    bool equalsIdPlayerNormal(Piece* piece, int numberOfMove);
    bool isEndOccupied(int idPlayer, int position);

    void leavePieceHome(Piece* piece);
    void leavePieceEnd(Piece* piece);
    void leavePieceNormal(Piece* piece);
};
#endif //UNTITLED_BOARD_H

