#pragma once
#include "board.h"

class Game {
private:
    int numberOfPlayers;
    Board* board;
    Piece* pieces[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_MAX_PLAYERS];
    //Player* players[NUMBER_OF_MAX_PLAYERS];
    int activeIdPlayer;

//    //moved piece
//    Type newTypeOfPiece;
//    int newPositionOfPiece;
//
//    //removed piece
//    int idPlayerOfRemovedPiece;
//    int numberOfRemovedPiece;
//    int newPositionOfRemovedPiece;

    //functions

    bool moveHomeStart(Piece* piece, int numberOfMove);
    void moveNormalHome(Piece* piece);
    bool moveNormal(Piece* piece, int numberOfMove);
    bool moveNormalEnd(Piece* piece, int startPosition, int numberOfMove);
    bool moveEndEnd(Piece* piece, int numberOfMove);
    Piece* getHomeFieldPiece(int idPlayer, int position);
    Piece* getEndFieldPiece(int idPlayer, int position);
    Piece* getNormalFieldPiece(int position);

//    void resetInfoPiece();
//    void setInfoRemovedPiece(Piece* removedPiece);
//    void setInfoMovedPiece(Piece* piece);
public:
    Game(int pNumberOfPlayers);
    ~Game();
    void start();

    void setActiveIdPlayer(int idPlayer);
    int getActiveIdPlayer();
    bool move(int piecePosition, int numberOfMove);
    bool isEnd();
    int getHomeFieldColor(int idPlayer, int position);
    int getHomeFieldNumber(int idPlayer, int position);
    int getEndFieldColor(int idPlayer, int position);
    int getEndFieldNumber(int idPlayer, int position);
    int getNormalFieldColor(int position);
    int getNormalFieldNumber(int position);

    //bool wasRemovedPiece();
//
//    Type getNewTypeOfPiece();
//    int getNewPositionOfPiece();
//    int getIdPlayerOfRemovedPiece();
//    int getNewPositionOfRemovedPiece();
//    int getNumberOfRemovedPiece();


};
