#ifndef UNTITLED_GUIPIECE_H
#define UNTITLED_GUIPIECE_H
class GUIPiece {
private:
    double x;
    double y;
public:
    GUIPiece(double pX, double pY);
    ~GUIPiece();


    double getX();
    double getY();
    void setX(double pX);
    void setY(double pY);
};
#endif //UNTITLED_GUIPIECE_H
