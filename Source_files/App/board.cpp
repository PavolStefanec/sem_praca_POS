#include "../../Header_files/App/board.h"
#include "../../Header_files/consts.h"
Board::Board(int pNumberOfPlayers) {
    numberOfPlayers = pNumberOfPlayers;

    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j  = 0; j < NUMBER_OF_PIECES; j++) {
            homeFields[i][j] = new Field(home);
            endFields[i][j] = new Field(end);
        }
        startFields[i] = new Field(start);
    }

    for (int i = 0; i < NUMBER_OF_GANE_FIELDS; i++) {
        normalFields[i] = new Field(normal);
    }
}

Board::~Board() {
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j  = 0; j < NUMBER_OF_PIECES; i++) {
            delete homeFields[i][j];
            delete endFields[i][j];
        }
        delete startFields[i];
    }

    for (int i = 0; i < NUMBER_OF_GANE_FIELDS; i++) {
       delete normalFields[i];
    }
}

bool Board::setPieceHome(Piece* piece, int idPlayer) {
    for (int i = 0; i < NUMBER_OF_PIECES; i++) {
        if (homeFields[idPlayer - 1][i]->getPiece() != nullptr) {
            homeFields[idPlayer - 1][i]->setPiece(piece);
            return true;
        }
    }
    return false;
}

bool Board::setPieceStart(Piece* piece, int idPlayer) {
    if (startFields[idPlayer - 1] != nullptr) {
        startFields[idPlayer - 1]->setPiece(piece);
        return true;
    }
    return false;
}

bool Board::setPieceEnd(Piece* piece, int idPlayer) {
    for (int i = 0; i < NUMBER_OF_PIECES; i++) {
        if (endFields[idPlayer - 1][i]->getPiece() != nullptr) {
            endFields[idPlayer - 1][i]->setPiece(piece);
            return true;
        }
    }
    return false;
}
bool Board::setPieceNormal(Piece* piece, int position) {
    if (normalFields[position - 1]->getPiece() != nullptr) {
        normalFields[position - 1]->setPiece(piece);
        return true;
    }
    return false;
}

Piece* Board::getPieceHome(int idPlayer, int position) {
    Piece* piece;
    if (homeFields[idPlayer - 1][position]->getPiece() != nullptr) {
        piece = homeFields[idPlayer - 1][position]->getPiece();
        //odstran figurku z policka
        homeFields[idPlayer - 1][position]->setPiece(nullptr);
        return piece;
    }
    return nullptr;
}

Piece* Board::getPieceStart(int idPlayer) {
    Piece* piece;
    if (startFields[idPlayer - 1]->getPiece() != nullptr) {
        piece = startFields[idPlayer - 1]->getPiece();
        //odstran figurku z policka
        startFields[idPlayer - 1]->setPiece(nullptr);
        return piece;
    }
    return nullptr;
}

Piece* Board::getPieceEnd(int idPlayer, int position) {
    Piece* piece;
    if (endFields[idPlayer - 1][position]->getPiece() != nullptr) {
        piece = homeFields[idPlayer - 1][position]->getPiece();
        //odstran figurku z policka
        endFields[idPlayer - 1][position]->setPiece(nullptr);
        return piece;
    }
    return nullptr;
}

Piece* Board::getPieceNormal(int position) {
    Piece* piece;
    if (normalFields[position]->getPiece() != nullptr) {
        piece = normalFields[position]->getPiece();
        //odstran figurku z policka
        normalFields[position]->setPiece(nullptr);
        return piece;
    }
    return nullptr;
}



