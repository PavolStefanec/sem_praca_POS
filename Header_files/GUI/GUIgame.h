#ifndef UNTITLED_GUIGAME_H
#define UNTITLED_GUIGAME_H
#include "GUIboard.h"
#include "GUIpiece.h"

class GUIGame {
private:
    GUIBoard* guiBoard;
    GUIPiece* guiPieces[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_PIECES];
    int numberOfPlayers;
public:
    GUIGame(string fileName, int pNumberOfPlayers);
    ~GUIGame();

};
#endif //UNTITLED_GUIGAME_H
