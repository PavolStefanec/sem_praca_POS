#include <iostream>
#include "Header_files/GUI/graphicsSystem.h"
#include "Header_files/App/piece.h"
#include "Header_files/App/game.h"
#include "Header_files/consts.h"
#include "Header_files/GUI/GUIgame.h"

#include "Header_files/communication/client.h"
#include "Header_files/communication/server.h"

int main(int argc, char* args[]) {
    Client *client = new Client();
        client->connectToServer("127.0.0.1", 9999);
        delete client;

    char* board = "C:\\Users\\miska\\Documents\\Data\\ProgramovacieJazyky\\C\\C++\\PrincipyOperacnychSystemov\\SemestralnaPraca2021\\sem_praca_POS\\Images\\gameBoard.png";
    char* pieces[4];
    pieces[0] = "C:\\Users\\miska\\Documents\\Data\\ProgramovacieJazyky\\C\\C++\\PrincipyOperacnychSystemov\\SemestralnaPraca2021\\sem_praca_POS\\Images\\red.png";
    pieces[1] = "C:\\Users\\miska\\Documents\\Data\\ProgramovacieJazyky\\C\\C++\\PrincipyOperacnychSystemov\\SemestralnaPraca2021\\sem_praca_POS\\Images\\blue.png";
    pieces[2] = "C:\\Users\\miska\\Documents\\Data\\ProgramovacieJazyky\\C\\C++\\PrincipyOperacnychSystemov\\SemestralnaPraca2021\\sem_praca_POS\\Images\\green.png";
    pieces[3] = "C:\\Users\\miska\\Documents\\Data\\ProgramovacieJazyky\\C\\C++\\PrincipyOperacnychSystemov\\SemestralnaPraca2021\\sem_praca_POS\\Images\\yellow.png";
    GUIGame* guiGame = new GUIGame("C:\\Users\\miska\\Documents\\Data\\ProgramovacieJazyky\\C\\C++\\PrincipyOperacnychSystemov\\SemestralnaPraca2021\\sem_praca_POS\\rozlozenieDosky.csv",board, pieces, 3);
    Game* game = new Game(3);

    game->setActiveIdPlayer(2);
    guiGame->setActiveIdPlayer(2);
    int piece = guiGame->clickEvent();
    if (piece != -1) {
            game->move(piece, 6);
            guiGame->setMovedPiece(game->getNewTypeOfPiece(),game->getNewPositionOfPiece());
        if (game->wasRemovedPiece()) {
            guiGame->setRemovedPiece(game->getIdPlayerOfRemovedPiece(), game->getNumberOfRemovedPiece(), game->getNewPositionOfRemovedPiece());
        }
        guiGame->redrawWindow();
    }
    piece = guiGame->clickEvent();
    if (piece != -1) {
        game->move(piece, 20);
        guiGame->setMovedPiece(game->getNewTypeOfPiece(),game->getNewPositionOfPiece());
        if (game->wasRemovedPiece()) {
            guiGame->setRemovedPiece(game->getIdPlayerOfRemovedPiece(), game->getNumberOfRemovedPiece(), game->getNewPositionOfRemovedPiece());
        }
        guiGame->redrawWindow();
    }
    piece = guiGame->clickEvent();
    if (piece != -1) {
        game->move(piece, 18);
        guiGame->setMovedPiece(game->getNewTypeOfPiece(),game->getNewPositionOfPiece());
        if (game->wasRemovedPiece()) {
            guiGame->setRemovedPiece(game->getIdPlayerOfRemovedPiece(), game->getNumberOfRemovedPiece(), game->getNewPositionOfRemovedPiece());
        }
        guiGame->redrawWindow();
    }
    piece = guiGame->clickEvent();
    if (piece != -1) {
        game->move(piece, 3);
        guiGame->setMovedPiece(game->getNewTypeOfPiece(),game->getNewPositionOfPiece());
        if (game->wasRemovedPiece()) {
            guiGame->setRemovedPiece(game->getIdPlayerOfRemovedPiece(), game->getNumberOfRemovedPiece(), game->getNewPositionOfRemovedPiece());
        }
        guiGame->redrawWindow();
    }
    while(true){}
    delete guiGame;
    delete game;
    return 0;
}