#ifndef BATTLESHIP_SEMESTRALKA_BATTLESHIP_H
#define BATTLESHIP_SEMESTRALKA_BATTLESHIP_H

class Battleship {

public:
    Battleship(int pX, int pY, int length, char orientation);
    ~Battleship() = default;
    int getX() {return x;};
    int getY() {return y;};
    int getLength() {return length;};
    int getOrientation() {return orientation;};

private:
    int x;
    int y;
    int length;
    char orientation;

};

#endif //BATTLESHIP_SEMESTRALKA_BATTLESHIP_H
