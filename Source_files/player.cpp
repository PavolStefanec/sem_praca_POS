#include "../Header_files/player.h"

Player::Player() {
    for (int i = 0; i < NUMBER_OF_PIECES; i++) {
        gamePiece[i] = new Piece();
    }
    activePlayer = false;
}

Player::~Player() {
    for (int i = 0; i < NUMBER_OF_PIECES; i++) {
        delete gamePiece[i];
    }
}

bool Player::getActivePlayer() {
    return activePlayer;
}

void Player::setActivePlayer(bool pActivePlayer) {
    activePlayer = pActivePlayer;
}


