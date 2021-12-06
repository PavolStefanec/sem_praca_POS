

#include "../../Header_files/GUI/GUIgame.h"

GUIGame::GUIGame(string fileName, char* boardPath, char* piecesPath[], int pNumberOfPlayers) {
    numberOfPlayers = pNumberOfPlayers;
    clicked = -1;
    activeIdPlayer = -1;
    guiBoard = new GUIBoard(fileName);
    graphicsSystem = new GraphicsSystem(numberOfPlayers,boardPath, piecesPath);
    for (int i = 1; i <= numberOfPlayers; i++) {
        for (int j = 0; j < NUMBER_OF_PIECES; j++) {
            int x = guiBoard->getHomeGUIFieldsX(i,j);
            int y = guiBoard->getHomeGUIFieldsY(i,j);
            guiPieces[i-1][j] = new GUIPiece(x,y);
            graphicsSystem->setTexturePiece(i,j,x,y);
        }
    }
    graphicsSystem->drawImages();
}

GUIGame::~GUIGame() {
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < NUMBER_OF_PIECES; j++) {
            delete guiPieces[i][j];
        }
    }
    delete guiBoard;
    delete graphicsSystem;
}

void GUIGame::redrawWindow() {
    graphicsSystem->clearWindow();
    graphicsSystem->drawImages();
}

int GUIGame::clickEvent() {
    int position[2];
    graphicsSystem->listenEvent(*position);
    if (position[0] != -1 && position[1] != -1) {
        for (int i = 0; i < NUMBER_OF_PIECES; i++) {
            if (guiPieces[activeIdPlayer - 1][i]->getX() <= position[0] &&
                position[0] <= guiPieces[activeIdPlayer - 1][i]->getX() + 40
                && guiPieces[activeIdPlayer - 1][i]->getY() <= position[1] &&
                position[1] <= guiPieces[activeIdPlayer - 1][i]->getY() + 40) {
                clicked = i;
                return i;
            }
        }
    }
    return -1;
}

void GUIGame::setMovedPiece(Type newType, int newPosition) {
    int x,y;
    if (newType == normal) {
        x = guiBoard->getNormalGUIFieldsX(newPosition);
        y = guiBoard->getNormalGUIFieldsY(newPosition);
    } else {
        x = guiBoard->getEndGUIFieldsX(activeIdPlayer, newPosition);
        y = guiBoard->getEndGUIFieldsY(activeIdPlayer, newPosition);
    }
    guiPieces[activeIdPlayer - 1][clicked]->setX(x);
    guiPieces[activeIdPlayer - 1][clicked]->setY(y);
    graphicsSystem->setTexturePiece(activeIdPlayer,clicked,x,y);
}

void GUIGame::setRemovedPiece(int idPlayer, int numberOfPiece, int newPosition) {
    int x,y;
    x = guiBoard->getHomeGUIFieldsX(idPlayer, newPosition);
    y = guiBoard->getHomeGUIFieldsY(idPlayer, newPosition);

    guiPieces[idPlayer - 1][numberOfPiece]->setX(x);
    guiPieces[idPlayer - 1][numberOfPiece]->setY(y);
    graphicsSystem->setTexturePiece(idPlayer,numberOfPiece,x,y);
}

void GUIGame::setActiveIdPlayer(int pIdPlayer) {
    activeIdPlayer = pIdPlayer;
}

