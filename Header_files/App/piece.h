#pragma once
#ifndef UNTITLED_GAMEPIECE_H
#define UNTITLED_GAMEPIECE_H
#include "player.h"

class Piece
{
private:
    int idPlayer;
    Type type;
    int color;
    int startFieldPosition;
    int goEndFieldPosition;
    int position;
    int numberOfPiece;

public:
    Piece(int pIdPlayer, int pStartFieldPosition, int pNumberOfPiece);
    ~Piece();

    int getIdPlayer();
    Type getType();
    int getStartFieldPosition();
    int getGoEndFieldPosition();
    int getPosition();
    int getNumberOfPiece();
    int getColor();

    void setType(Type pType);
    void setPosition(int pPosition);
};

#endif //UNTITLED_GAMEPIECE_H
