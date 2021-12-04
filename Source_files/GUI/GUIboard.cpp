#include "../../Header_files/GUI/GUIboard.h"
#include "../../Header_files/input.file.h"

GUIBoard::GUIBoard(string fileName) {
    InputFile* reader = new InputFile();
    successReading = reader->openFile(fileName);
    if (successReading) {
        for (int i = 0; i < NUMBER_OF_MAX_PLAYERS; i++) {
            for (int j = 0; j < NUMBER_OF_PIECES; j++) {
                reader->nextLine();
                int x = stoi(reader->readWord());
                int y = stoi(reader->readWord());
                homeGUIFields[i][j] = new GUIField(x,y);
            }
        }

        for (int i = 0; i < NUMBER_OF_MAX_PLAYERS; i++) {
            reader->nextLine();
            startGUIFields[i] = new GUIField(stoi(reader->readWord()), stoi(reader->readWord()));
        }

        for (int i = 0; i < NUMBER_OF_MAX_PLAYERS; i++) {
            for (int j = 0; j < NUMBER_OF_PIECES; j++) {
                reader->nextLine();
                endGUIFields[i][j] = new GUIField(stoi(reader->readWord()), stoi(reader->readWord()));
            }
        }

        for (int i = 0; i < NUMBER_OF_GANE_FIELDS; i++) {
            reader->nextLine();
            normalGUIFields[i] = new GUIField(stoi(reader->readWord()), stoi(reader->readWord()));
        }
        reader->closeFile();
    }
    delete reader;
}

GUIBoard::~GUIBoard() {
    for (int i = 0; i < NUMBER_OF_MAX_PLAYERS; i++) {
        for (int j = 0; j < NUMBER_OF_PIECES; j++) {
            delete homeGUIFields[i][j];
            delete endGUIFields[i][j];
        }
        delete startGUIFields[i];
    }

    for (int i = 0; i < NUMBER_OF_GANE_FIELDS; i++) {
        delete normalGUIFields[i];
    }
}

int GUIBoard::getHomeGUIFieldsX(int idPlayer, int position) {
    return homeGUIFields[idPlayer - 1][position]->getX();
}

int GUIBoard::getHomeGUIFieldsY(int idPlayer, int position) {
    return homeGUIFields[idPlayer - 1][position]->getY();
}

int GUIBoard::getStartGUIFieldsX(int idPlayer) {
    return startGUIFields[idPlayer - 1]->getX();
}

int GUIBoard::getStartGUIFieldsY(int idPlayer) {
    return startGUIFields[idPlayer - 1]->getY();
}

int GUIBoard::getEndGUIFieldsX(int idPlayer, int position) {
    return endGUIFields[idPlayer - 1][position]->getX();
}

int GUIBoard::getEndGUIFieldsY(int idPlayer, int position) {
    return endGUIFields[idPlayer - 1][position]->getY();
}

int GUIBoard::getNormalGUIFieldsX(int position) {
    return normalGUIFields[position]->getX();
}

int GUIBoard::getNormalGUIFieldsY(int position) {
    return normalGUIFields[position]->getY();
}

