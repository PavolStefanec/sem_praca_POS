#pragma once
#include "board.h"

class Game {
private:
    int numberOfPlayers;
    Board* board;
    Piece* pieces[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_MAX_PLAYERS];
    int activeIdPlayer;

    //functions

    bool moveHomeStart(Piece* piece, int numberOfMove);
    void moveNormalHome(Piece* piece);
    bool moveNormal(Piece* piece, int numberOfMove);
    bool moveNormalEnd(Piece* piece, int startPosition, int numberOfMove);
    bool moveEndEnd(Piece* piece, int numberOfMove);

public:
    Game(int pNumberOfPlayers);
    ~Game();
    void start();
    int getActiveIdPlayer();
    void setActiveIdPlayer(int idPlayer);
    bool move(int piecePosition, int numberOfMove);
    bool isEnd();
    int getHomeFieldColor(int idPlayer, int position);
    int getHomeFieldNumber(int idPlayer, int position);
    int getEndFieldColor(int idPlayer, int position);
    int getEndFieldNumber(int idPlayer, int position);
    int getNormalFieldColor(int position);
    int getNormalFieldNumber(int position);
};
