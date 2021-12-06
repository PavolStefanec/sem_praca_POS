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
    int clicked;
    int activeIdPlayer;

    //funcitons
public:
    GUIGame(string fileName, char* boardPath, char* piecesPath[], int pNumberOfPlayers);
    ~GUIGame();
    int clickEvent();
    void setMovedPiece(Type newType, int newPosition);
    void setRemovedPiece(int idPlayer, int numberOfPiece, int newPosition);
    void redrawWindow();
    void setActiveIdPlayer(int pIdPlayer);
};
#endif //UNTITLED_GUIGAME_H
