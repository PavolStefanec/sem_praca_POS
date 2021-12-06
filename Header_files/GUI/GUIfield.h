#ifndef UNTITLED_GUIFIELD_H
#define UNTITLED_GUIFIELD_H
class GUIField {
private:
    int x;
    int y;
public:
    GUIField(int pX, int pY);
    ~GUIField();

    int getX();
    int getY();
};
#endif //UNTITLED_GUIFIELD_H
