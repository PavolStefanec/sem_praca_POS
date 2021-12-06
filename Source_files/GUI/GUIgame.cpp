

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

bool GUIGame::controlClick(int x, int y) {
    return false;
}

int GUIGame::getPiecePosition(int idPlayer) {
    for (int i = 0; i < NUMBER_OF_PIECES; i++) {
        if (controlClick(guiPieces[idPlayer - 1][i]->getX(), guiPieces[idPlayer - 1][i]->getY())) {
            return i;
        };
    }
    return -1;
}

