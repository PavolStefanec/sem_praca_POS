#pragma once
#ifndef UNTITLED_GAMEPIECE_H
#define UNTITLED_GAMEPIECE_H
#include "player.h"

class Piece
{
private:
    int idPlayer;
    Type type;
    int position;
public:
    Piece(int idPlayer);
    ~Piece();

    int getIdPlayer();
    Type getType();
    int getPosition();

    void setIdPlayer(int pIdPlayer);
    void setType(Type pType);
    void setPosition(int pPosition);
};

#endif //UNTITLED_GAMEPIECE_H
