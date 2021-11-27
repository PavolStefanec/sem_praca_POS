#pragma once

#include "consts.h"
#include "piece.h"

using namespace std;

class Player
{
private:
    Piece* gamePiece[NUMBER_OF_PIECE];
    bool activePlayer;
public:
    Player();
    ~Player();
    bool getActivePlayer();
    void setActivePlayer(bool pActivePlayer);
};
