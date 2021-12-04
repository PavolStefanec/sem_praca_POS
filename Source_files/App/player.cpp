#include "../../Header_files/App/player.h"

Player::Player(int pIdPlayer) {
    idPlayer = pIdPlayer;
    activePlayer = false;
}

Player::~Player() {}

bool Player::getActivePlayer() {
    return activePlayer;
}

void Player::setActivePlayer(bool pActivePlayer) {
    activePlayer = pActivePlayer;
}


