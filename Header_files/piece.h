#ifndef UNTITLED_GAMEPIECE_H
#define UNTITLED_GAMEPIECE_H


class Piece
{
private:
    bool isHome;
public:
    Piece();
    ~Piece();
    bool getIsHome();
    void setIsHome(bool pIsHome);
};

#endif //UNTITLED_GAMEPIECE_H
