#include "../Header_files/console.h"

Console::Console(int numberOfPlayer) {
    game = new Game(numberOfPlayer);
    activePlayer = -1;
}

Console::~Console() {
    delete game;
}

void Console::start() {
    game->start();
}

int Console::getNumberOfPiece() {
    cout<<"\033[1;" << COLOR_NUMBER + activePlayer - 1 <<"m Stlač číslo figúrky 1-4 a 0, ak chceš svoj ťah preskočiť! \033[0m"<<endl;
    cout<<"\033[1;" << COLOR_NUMBER + activePlayer - 1 <<"m Číslo figúrky: \033[0m";
    int pieceNumber;
    cin >> pieceNumber;
    cout << endl;
    if (pieceNumber == 0)
        cout<<"\033[1;" << COLOR_NUMBER + activePlayer - 1 <<"m Preskakuješ ťah! \033[0m"<<endl;
    if (pieceNumber < 0 || pieceNumber > 5) {
        cout<<"\033[1;" << COLOR_NUMBER + activePlayer - 1 <<"m Zvolené figúrka neexistuje! \033[0m"<<endl;
    }
    return pieceNumber;
}

void Console::drawBoard() {
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

void Console::drawSpace(int count) {
    cout << std::string(count, ' ');
}

void Console::drawHome(int idPlayer, int position) {
    for (int i = 0; i < 2; i++) {
        cout<< "\033[1;" << game->getHomeFieldColor(idPlayer, position + i) << "m" << game->getHomeFieldNumber(idPlayer, position + i) << "\033[0m";
        cout << " ";
    }
}

void Console::drawNormal(int count, int position, bool positive) {
    for (int i = 0; i < count; i++) {
        if (positive) {
            cout<< "\033[1;" << game->getNormalFieldColor(position + i) << "m" << game->getNormalFieldNumber(position + i) << "\033[0m";
        } else {
            cout<< "\033[1;" << game->getNormalFieldColor(position - i) << "m" << game->getNormalFieldNumber(position - i) << "\033[0m";
        }
        cout << " ";
    }
}

void Console::drawEnd(int idPlayer, int position, int count, bool positive) {
    for (int i = 0; i < count; i++) {
        if (positive) {
            cout<< "\033[1;" << game->getEndFieldColor(idPlayer, position + i) << "m" << game->getEndFieldNumber(idPlayer,position + i)<< "\033[0m";
        } else {
            cout<< "\033[1;" << game->getEndFieldColor(idPlayer, position - i) << "m" << game->getEndFieldNumber(idPlayer,position - i)<< "\033[0m";
        }
        cout << " ";
    }
}

void Console::drawFirstLineWithHome(int idPlayer1, int idPlayer2, int position, bool positive) {
    cout << "|";
    drawSpace(1);
    drawHome(idPlayer1,0);
    drawSpace(4);
    drawNormal(3, position, positive);
    drawSpace(4);
    drawHome(idPlayer2,0);
    cout<<"|"<<endl;
}

void Console::drawSecondLineWithHome(int idPlayer1, int idPlayer2, int idPlayer3, int position1, int position2) {
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

void Console::drawShortLine(int position1, int position2, int idPlayer, int positionEnd) {
    cout << "|";
    drawSpace(9);
    drawNormal(1, position1);
    drawEnd(idPlayer, positionEnd, 1);
    drawNormal(1, position2);
    drawSpace(8);
    cout << "|" << endl;
}

void Console::drawLongLine(int position1, int position2, int idPlayer, int positionEnd, bool positive) {
    cout << "|";
    drawSpace(1);
    drawNormal(5, position1,positive);
    drawEnd(idPlayer,positionEnd,1);
    drawNormal(5, position2,positive);
    cout<<"|"<<endl;
}

void Console::clear() {
    cout << "\033[2J\033[1;1H";
}

void Console::setActivePlayer(int idPlayer) {
    activePlayer = idPlayer;
    game->setActiveIdPlayer(idPlayer);
}

void Console::move(int number, int position) {
    game->move(position -1, number);
}


bool Console::isEnd() {
    return game->isEnd();
}
