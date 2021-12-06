

#include "../../Header_files/GUI/GUIgame.h"

GUIGame::GUIGame(string fileName, int pNumberOfPlayers) {
    numberOfPlayers = pNumberOfPlayers;
    guiBoard = new GUIBoard(fileName);
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < NUMBER_OF_PIECES; j++) {
            guiPieces[i][j] = new GUIPiece(guiBoard->getHomeGUIFieldsX(i,j),guiBoard->getHomeGUIFieldsY(i,j));
        }
    }
}

GUIGame::~GUIGame() {
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < NUMBER_OF_PIECES; j++) {
            delete guiPieces[i][j];
        }
    }
    delete guiBoard;
}

