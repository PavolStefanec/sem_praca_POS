#ifndef UNTITLED_GUIBOARD_H
#define UNTITLED_GUIBOARD_H
#include "GUIfield.h"
#include "../consts.h"
#include <string>
using namespace std;

class GUIBoard {
private:
    bool successReading;
    GUIField* homeGUIFields[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_MAX_PLAYERS];
    GUIField* endGUIFields[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_MAX_PLAYERS];
    GUIField* normalGUIFields[NUMBER_OF_GANE_FIELDS];
public:
    GUIBoard(string fileName);
    ~GUIBoard();

    int getHomeGUIFieldsX(int idPlayer, int position);
    int getHomeGUIFieldsY(int idPlayer, int position);
    int getEndGUIFieldsX(int idPlayer, int position);
    int getEndGUIFieldsY(int idPlayer, int position);
    int getNormalGUIFieldsX(int position);
    int getNormalGUIFieldsY(int position);


};
#endif //UNTITLED_GUIBOARD_H
