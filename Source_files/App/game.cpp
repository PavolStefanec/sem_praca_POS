#include "../../Header_files/App/game.h"

Game::Game(int pNumberOfPlayers){
    numberOfPlayers = pNumberOfPlayers;
    for (int i = 0; i < numberOfPlayers; i++) {
        players[i] = new Player(i + 1);
    }
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < numberOfPlayers; j++) {
            pieces[i][j] = new Piece(i + 1);
        }
    }
    board = new Board(numberOfPlayers);
}

Game::~Game() {
    for (int i = 0; i < numberOfPlayers; i++) {
        delete players[i];
    }
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < numberOfPlayers; j++) {
            delete pieces[i][j];
        }
    }
    delete board;
}

void Game::start() {
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < NUMBER_OF_PIECES; j++) {
            board->setPieceHome(pieces[i][j],i+1);
            pieces[i][j]->setType(home);
            pieces[i][j]->setPosition(j);
        }
    }
}

bool Game::isEnd(int idPlayer) {
    for (int i = 0; i < NUMBER_OF_PIECES; i++) {
        if (board->getPieceEnd(idPlayer,i) == nullptr) {
            return false;
        }
    }
    return true;
}


