#include "../Header_files/interface.h"

Interface::Interface(int numberOfPlayer) {
    game = new Game(numberOfPlayer);
    activePlayer = -1;
}

Interface::~Interface() {
    delete game;
}

void Interface::start() {
    game->start();
}

int Interface::getNumberOfPiece(int value) {
    cout<<"\033[1;" << COLOR_NUMBER + activePlayer - 1 <<"m Hodil si číslo: \033[0m"<< value <<endl;
    cout<<"\033[1;" << COLOR_NUMBER + activePlayer - 1 <<"m Stlač číslo figúrky 1-4 a 0, ak chceš svoj ťah preskočiť! \033[0m"<<endl;
    cout<<"\033[1;" << COLOR_NUMBER + activePlayer - 1 <<"m Číslo figúrky: \033[0m";
    char pieceNumberCH;
    int pieceNumber;
    cin >> pieceNumberCH;
    cout << endl;
    if (pieceNumberCH == '0') {
        cout << "\033[1;" << COLOR_NUMBER + activePlayer - 1 << "m Preskakuješ ťah! \033[0m" << endl;
        pieceNumber = 0;
    }
    else if (pieceNumberCH < '0' || pieceNumberCH > '5') {
        cout<<"\033[1;" << COLOR_NUMBER + activePlayer - 1 <<"m Zvolené figúrka neexistuje! \033[0m"<<endl;
        pieceNumber = 0;
    } else {
        pieceNumber = pieceNumberCH - 48;
    }
    return pieceNumber;
}

void Interface::drawBoard() {
    cout << "-------------------------" <<endl;
    drawFirstLineWithHome(1,2,8);
    drawSecondLineWithHome(1,2,2,7,11);
    drawShortLine(6,12,2,1);
    drawShortLine(5,13,2,2);
    drawLongLine(0,14,2,3);
    cout << "|";
    drawSpace(1);
    drawNormal(1, 39);
    drawEnd(1,0,4);
    drawSpace(2);
    drawEnd(3,3,4, false);
    drawNormal(1, 19);
    cout<<"|"<<endl;
    drawLongLine(38,24,4,3,false);
    drawShortLine(33,25,4,2);
    drawShortLine(32,26,4,1);
    drawSecondLineWithHome(4,3,4,31,27);
    drawFirstLineWithHome(4,3,30,false);
    cout << "-------------------------" <<endl;
}

void Interface::drawSpace(int count) {
    cout << std::string(count, ' ');
}

void Interface::drawHome(int idPlayer, int position) {
    for (int i = 0; i < 2; i++) {
        cout<< "\033[1;" << game->getHomeFieldColor(idPlayer, position + i) << "m" << game->getHomeFieldNumber(idPlayer, position + i) << "\033[0m";
        cout << " ";
    }
}

void Interface::drawNormal(int count, int position, bool positive) {
    for (int i = 0; i < count; i++) {
        if (positive) {
            cout<< "\033[1;" << game->getNormalFieldColor(position + i) << "m" << game->getNormalFieldNumber(position + i) << "\033[0m";
        } else {
            cout<< "\033[1;" << game->getNormalFieldColor(position - i) << "m" << game->getNormalFieldNumber(position - i) << "\033[0m";
        }
        cout << " ";
    }
}

void Interface::drawEnd(int idPlayer, int position, int count, bool positive) {
    for (int i = 0; i < count; i++) {
        if (positive) {
            cout<< "\033[1;" << game->getEndFieldColor(idPlayer, position + i) << "m" << game->getEndFieldNumber(idPlayer,position + i)<< "\033[0m";
        } else {
            cout<< "\033[1;" << game->getEndFieldColor(idPlayer, position - i) << "m" << game->getEndFieldNumber(idPlayer,position - i)<< "\033[0m";
        }
        cout << " ";
    }
}

void Interface::drawFirstLineWithHome(int idPlayer1, int idPlayer2, int position, bool positive) {
    cout << "|";
    drawSpace(1);
    drawHome(idPlayer1,0);
    drawSpace(4);
    drawNormal(3, position, positive);
    drawSpace(4);
    drawHome(idPlayer2,0);
    cout<<"|"<<endl;
}

void Interface::drawSecondLineWithHome(int idPlayer1, int idPlayer2, int idPlayer3, int position1, int position2) {
    cout << "|";
    drawSpace(1);
    drawHome(idPlayer1,2);
    drawSpace(4);
    drawNormal(1, position1);
    drawEnd(idPlayer3,0,1);
    drawNormal(1, position2);
    drawSpace(4);
    drawHome(idPlayer2,2);
    cout<<"|"<<endl;
}

void Interface::drawShortLine(int position1, int position2, int idPlayer, int positionEnd) {
    cout << "|";
    drawSpace(9);
    drawNormal(1, position1);
    drawEnd(idPlayer, positionEnd, 1);
    drawNormal(1, position2);
    drawSpace(8);
    cout << "|" << endl;
}

void Interface::drawLongLine(int position1, int position2, int idPlayer, int positionEnd, bool positive) {
    cout << "|";
    drawSpace(1);
    drawNormal(5, position1,positive);
    drawEnd(idPlayer,positionEnd,1);
    drawNormal(5, position2,positive);
    cout<<"|"<<endl;
}

void Interface::setActivePlayer(int idPlayer) {
    activePlayer = idPlayer;
    game->setActiveIdPlayer(idPlayer);
}

void Interface::move(int number, int position) {
    if (game->move(position -1, number)) {
        cout<< "\033[1;" << COLOR_NUMBER + activePlayer -1 << "m Ťah sa podarilo vykonať! \033[0m" << endl;
    } else {
        cout<< "\033[1;" << COLOR_NUMBER + activePlayer -1 << "m Ťah sa nepodarilo vykonať! \033[0m" << endl;
    }
}

bool Interface::isEnd() {
    return game->isEnd();
}