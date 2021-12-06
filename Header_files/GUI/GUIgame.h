#ifndef UNTITLED_GUIGAME_H
#define UNTITLED_GUIGAME_H
#include "GUIboard.h"
#include "GUIpiece.h"
#include "graphicsSystem.h"

class GUIGame {
private:
    GraphicsSystem* graphicsSystem;
    GUIBoard* guiBoard;
    GUIPiece* guiPieces[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_PIECES];
    int numberOfPlayers;
public:
    GUIGame(string fileName, int pNumberOfPlayers);
    ~GUIGame();
    bool controlClick(int x, int y);
    int getPiecePosition(int idPlayer);

};
#endif //UNTITLED_GUIGAME_H
