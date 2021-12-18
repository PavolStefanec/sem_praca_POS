#pragma once
#include "../consts.h"
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