#pragma once
#ifndef UNTITLED_GAMEPIECE_H
#define UNTITLED_GAMEPIECE_H
#include "player.h"

class Piece
{
private:
    int idPlayer;
    Type type;
    int startFieldPosition;
    int goEndFieldPosition;
    int position;

public:
    Piece(int pIdPlayer, int pStartFieldPosition);
    ~Piece();

    int getIdPlayer();
    Type getType();
    int getStartFieldPosition();
    int getGoEndFieldPosition();
    int getPosition();

    void setType(Type pType);
    void setPosition(int pPosition);
};

#endif //UNTITLED_GAMEPIECE_H
