#pragma once
#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include "../consts.h"
#include "piece.h"

using namespace std;

class Player
{
private:
    int idPlayer;
    bool activePlayer;
public:
    Player(int pIdPlayer);
    ~Player();
    bool getActivePlayer();
    void setActivePlayer(bool pActivePlayer);
};
#endif //UNTITLED_PLAYER_H


