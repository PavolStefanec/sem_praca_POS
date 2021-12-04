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
    Field* startFields[NUMBER_OF_MAX_PLAYERS];
    Field* normalFields[NUMBER_OF_GANE_FIELDS];
public:
    Board(int numberOfPlayer);
    ~Board();

    bool setPieceHome(Piece* piece, int idPlayer);
    bool setPieceStart(Piece* piece, int idPlayer);
    bool setPieceEnd(Piece* piece, int idPlayer);
    bool setPieceNormal(Piece* piece, int position);

    Piece* getPieceHome(int idPlayer, int position);
    Piece* getPieceStart(int idPlayer);
    Piece* getPieceEnd(int idPlayer, int position);
    Piece* getPieceNormal(int position);
};
#endif //UNTITLED_BOARD_H

