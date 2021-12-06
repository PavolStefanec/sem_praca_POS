#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H
#include "../consts.h"
#include "board.h"
#include "player.h"

class Game {
private:
    int numberOfPlayers;
    Board* board;
    Piece* pieces[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_MAX_PLAYERS];
    Player* players[];
public:
    Game(int pNumberOfPlayers);
    ~Game();
    void start();
    bool isEnd(int idPlayer);
};
#endif //UNTITLED_GAME_H
