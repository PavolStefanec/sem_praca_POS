#include "App/game.h"
#include <iostream>

using namespace std;

class Console{
private:
    Game* game;
    int activePlayer;
    //functions

    //pomocne
    void drawSpace(int count);
    void drawHome(int idPlayer, int position);
    void drawNormal(int count, int position, bool positive = true);
    void drawEnd(int idPlayer, int position, int count,bool positive = true);

    //line
    void drawFirstLineWithHome(int idPlayer1, int idPlayer2, int position, bool positive = true);
    void drawSecondLineWithHome(int idPlayer1, int idPlayer2, int idPlayer3, int position1, int position2);
    void drawShortLine(int position1, int position2, int idPlayer, int positionEnd);
    void drawLongLine(int position1, int position2, int idPlayer, int positionEnd, bool positive = true);

public:
    Console(int numberOfPlayer);
    ~Console();
    void setActivePlayer(int idPlayer);
    int getNumberOfPiece();
    void start(int numberOfPlayer);
    void drawBoard();
    void clear();
    void move(int number);
};

