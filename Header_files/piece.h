#pragma once

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
