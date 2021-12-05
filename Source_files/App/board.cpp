#include "../../Header_files/App/board.h"
#include "../../Header_files/consts.h"

//public

Board::Board(int pNumberOfPlayers) {
    numberOfPlayers = pNumberOfPlayers;

    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j  = 0; j < NUMBER_OF_PIECES; j++) {
            homeFields[i][j] = new Field(home);
            endFields[i][j] = new Field(end);
        }
    }

    for (int i = 0; i < NUMBER_OF_GANE_FIELDS; i++) {
        normalFields[i] = new Field(normal);
    }
}

Board::~Board() {
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j  = 0; j < NUMBER_OF_PIECES; j++) {
            delete homeFields[i][j];
            delete endFields[i][j];
        }
    }

    for (int i = 0; i < NUMBER_OF_GANE_FIELDS; i++) {
       delete normalFields[i];
    }
}

Piece *Board::setNormal(Piece *piece, int position) {
    Piece* removedPiece = getRemovedPieceNormal(position);
    setPieceNormal(piece,position);
    return removedPiece;
}

void Board::setHome(Piece* piece) {
    for (int i = 0; i < NUMBER_OF_PIECES; i++) {
        if (homeFields[piece->getIdPlayer() - 1][i]->getPiece() == nullptr) {
            setPieceHome(piece, i);
            return;
        }
    }
}

void Board::setPieceHome(Piece *piece, int position) {
    //zmen figurku
    homeFields[piece->getIdPlayer()-1][position]->setPiece(piece);
    //zmen info vo figurke
    piece->setType(home);
    piece->setPosition(position);
}

void Board::setEnd(Piece* piece, int position) {
    endFields[piece->getIdPlayer() - 1][position]->setPiece(piece);
    piece->setType(end);
    piece->setPosition(position);;
}

bool Board::equalsIdPlayerStart(Piece *piece) {
    Piece* actualPiece = normalFields[piece->getStartFieldPosition()]->getPiece();
    if (actualPiece != nullptr)
        return actualPiece->getIdPlayer() == piece->getIdPlayer();
    else
        return false;
}

bool Board::equalsIdPlayerNormal(Piece *piece, int numberOfMove) {
    Piece* actualPiece = normalFields[piece->getPosition() + numberOfMove]->getPiece();
    if (actualPiece != nullptr)
        return actualPiece->getIdPlayer() == piece->getIdPlayer();
    else
        return false;
}

bool Board::isEndOccupied(int idPlayer, int position) {
    return endFields[idPlayer-1][position]->getPiece() == nullptr ? false : true;
}

void Board::leavePieceHome(Piece *piece) {
    homeFields[piece->getIdPlayer()-1][piece->getPosition()]->setPiece(nullptr);
}

void Board::leavePieceEnd(Piece *piece) {
    endFields[piece->getIdPlayer()-1][piece->getPosition()]->setPiece(nullptr);
}

void Board::leavePieceNormal(Piece *piece) {
    normalFields[piece->getPosition()]->setPiece(nullptr);
}

//private

Piece* Board::getRemovedPieceNormal(int position) {
    Piece* piece;
    if (normalFields[position]->getPiece() != nullptr) {
        piece = normalFields[position]->getPiece();
        //odstran figurku z policka
        leavePieceNormal(piece);
        return piece;
    }
    return nullptr;
}

void Board::setPieceNormal(Piece* piece, int position) {
    normalFields[position]->setPiece(piece);
    //nadstav info vo figurke
    piece->setType(normal);
    piece->setPosition(position);
}