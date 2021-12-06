#include "../../Header_files/App/game.h"

//public

Game::Game(int pNumberOfPlayers){
    numberOfPlayers = pNumberOfPlayers;
    resetInfoPiece();
    for (int i = 0; i < numberOfPlayers; i++) {
        players[i] = new Player(i + 1);
    }
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < NUMBER_OF_PIECES; j++) {
            pieces[i][j] = new Piece(i + 1,i * FIELDS_BEWTWEEN_TWO_STARTS);
        }
    }
    board = new Board(numberOfPlayers);
}

Game::~Game() {
    for (int i = 0; i < numberOfPlayers; i++) {
        delete players[i];
    }
    //figurky mazem v board
    delete board;
}

void Game::start() {
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < NUMBER_OF_PIECES; j++) {
            board->setPieceHome(pieces[i][j],j);
        }
    }
}

bool Game::move(int idPlayer, int piecePosition, int numberOfMove) {
    resetInfoPiece();
    Piece* piece = pieces[idPlayer-1][piecePosition];
    switch (piece->getType()) {
        case home:
            return moveHomeStart(piece, numberOfMove);
        case normal:
            return moveNormal(piece, numberOfMove);
        case end:
            return moveEndEnd(piece,numberOfMove);
    }

}

bool Game::isEnd(int idPlayer) {
    for (int i = 0; i < NUMBER_OF_PIECES; i++) {
        if (!board->isEndOccupied(idPlayer,i)) {
            return false;
        }
    }
    return true;
}

//private

bool Game::moveHomeStart(Piece *piece, int numberOfMove) {
    if (numberOfMove == SIX) {
        if (board->equalsIdPlayerStart(piece)) {
            return false;
        }
        //vycisti policko, na ktorom si doteraz stal
        board->leavePieceHome(piece);
        //vyhod figurku
        Piece* removedPiece = board->setNormal(piece, piece->getStartFieldPosition());
        if (removedPiece != nullptr) {
            moveNormalHome(removedPiece);
        }
        setInfoMovedPiece(piece);
        return true;
    }
    return false;
}

void Game::moveNormalHome(Piece *piece) {
    board->setHome(piece);
    setInfoRemovedPiece(piece);
}

bool Game::moveNormal(Piece *piece, int numberOfMove) {
    int position = piece->getPosition();

    //prekrocenie velkosti pola okrem cerveneho hraca
    if (position + numberOfMove >= NUMBER_OF_GANE_FIELDS && piece->getStartFieldPosition() != 0) {
        numberOfMove = numberOfMove - (NUMBER_OF_GANE_FIELDS - position);
        position = 0;
    } else
        //ide cerveny do domceka?
    if (position + numberOfMove >= NUMBER_OF_GANE_FIELDS && piece->getStartFieldPosition() == 0) {
        return moveNormalEnd(piece, 0, position+numberOfMove-piece->getGoEndFieldPosition() - 1);
    } else
        //idu ostatni do domceka?
    if (position < piece->getStartFieldPosition() && position + numberOfMove > piece->getStartFieldPosition()) {
        return moveNormalEnd(piece,0, position+numberOfMove-piece->getGoEndFieldPosition() - 1);
    }
    //nevyhodim seba?
    if (board->equalsIdPlayerNormal(piece, numberOfMove)){
        return false;
    } else {
        //vycisti policko, na ktorom stojis
        board->leavePieceNormal(piece);
        //posun fiigurku a ak sa niekto nachadza na policku, tak ho vyhod
        Piece* removedPiece = board->setNormal(piece, numberOfMove + position);
        //uloz odstranenu figurku, ktoru treba vratit do domceka
        if (removedPiece != nullptr) {
            moveNormalHome(removedPiece);
        }
        setInfoMovedPiece(piece);
        return true;
    }
}

bool Game::moveNormalEnd(Piece *piece, int startPosition, int numberOfMove) {
    //prekrocenie dlzky pola
    if (numberOfMove >= NUMBER_OF_PIECES - startPosition) {
        return false;
    }
    if (board->isEndOccupied(piece->getIdPlayer(), startPosition + numberOfMove)) {
        return false;
    }
    //vycisti policko, na ktorom si doteraz stal
    board->leavePieceNormal(piece);
    //posun v endFiles
    board->setEnd(piece, numberOfMove);
    setInfoMovedPiece(piece);
    return true;
}


bool Game::moveEndEnd(Piece *piece, int numberOfMove) {
    //prekrocenie dlzky pola
    if (numberOfMove >= NUMBER_OF_PIECES - piece->getPosition()) {
        return false;
    }
    if (board->isEndOccupied(piece->getIdPlayer(), piece->getPosition() + numberOfMove)) {
        return false;
    }
    //vycisti policko, na ktorom si doteraz stal
    board->leavePieceEnd(piece);
    //posun v endFiles
    board->setEnd(piece, piece->getPosition() + numberOfMove);
    setInfoMovedPiece(piece);
    return true;
}

void Game::resetInfoPiece() {
    newTypeOfPiece = none;
    newPositionOfPiece = -1;
    idPlayerOfRemovedPiece = -1;
    newPositionOfRemovedPiece = -1;
}

void Game::setInfoRemovedPiece(Piece* removedPiece) {
    idPlayerOfRemovedPiece = removedPiece->getIdPlayer();
    newPositionOfRemovedPiece = removedPiece->getPosition();
}

void Game::setInfoMovedPiece(Piece *piece) {
    newTypeOfPiece = piece->getType();
    newPositionOfPiece = piece->getPosition();
}

bool Game::wasRemovedPiece() {
    if (idPlayerOfRemovedPiece == -1)
        return false;
    return true;
}

int Game::getNewPositionOfPiece() {
    return newPositionOfPiece;
}

int Game::getIdPlayerOfRemovedPiece() {
    return idPlayerOfRemovedPiece;
}

int Game::getNewPositionOfRemovedPiece() {
    return newPositionOfRemovedPiece;
}




