#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H
#include "../consts.h"
#include "board.h"
#include "player.h"

class Game {
private:
    int numberOfPlayers;
    Board* board;
    Piece* pieces[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_MAX_PLAYERS];
    Player* players[NUMBER_OF_MAX_PLAYERS];
    Type newTypeOfPiece;
    int newPositionOfPiece;
    int idPlayerOfRemovedPiece;
    int newPositionOfRemovedPiece;

    //functions

    bool moveHomeStart(Piece* piece, int numberOfMove);
    void moveNormalHome(Piece* piece);
    bool moveNormal(Piece* piece, int numberOfMove);
    bool moveNormalEnd(Piece* piece, int startPosition, int numberOfMove);
    bool moveEndEnd(Piece* piece, int numberOfMove);

    void resetInfoPiece();
    void setInfoRemovedPiece(Piece* removedPiece);
    void setInfoMovedPiece(Piece* piece);
public:
    Game(int pNumberOfPlayers);
    ~Game();
    void start();
    bool move(int idPlayer, int piecePosition, int numberOfMove);
    bool isEnd(int idPlayer);

    bool wasRemovedPiece();

    int getNewPositionOfPiece();
    int getIdPlayerOfRemovedPiece();
    int getNewPositionOfRemovedPiece();


};
#endif //UNTITLED_GAME_H
