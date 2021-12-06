#include "../../Header_files/GUI/GUIboard.h"
#include "../../Header_files/input.file.h"

GUIBoard::GUIBoard(string fileName) {
    InputFile* reader = new InputFile();
    successReading = reader->openFile(fileName);
    if (successReading) {
        reader->nextLine();
        for (int i = 0; i < NUMBER_OF_MAX_PLAYERS; i++) {
            for (int j = 0; j < NUMBER_OF_PIECES; j++) {
                reader->nextLine();
                string word1 = reader->readWord();
                string word2 = reader->readWord();
                homeGUIFields[i][j] = new GUIField(stoi(word1),stoi(word2));
            }
        }
        for (int i = 0; i < NUMBER_OF_MAX_PLAYERS; i++) {
            for (int j = 0; j < NUMBER_OF_PIECES; j++) {
                reader->nextLine();
                string word1 = reader->readWord();
                string word2 = reader->readWord();
                endGUIFields[i][j] = new GUIField(stoi(word1), stoi(word2));
            }
        }

        for (int i = 0; i < NUMBER_OF_GANE_FIELDS; i++) {
            reader->nextLine();
            string word1 = reader->readWord();
            string word2 = reader->readWord();
            normalGUIFields[i] = new GUIField(stoi(word1), stoi(word2));
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


