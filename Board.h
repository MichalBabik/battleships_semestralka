#include <functional>
#include "Battleship.h"
#include <string>

#ifndef BATTLESHIPS_SEMESTRALKA_BOARD_H
#define BATTLESHIPS_SEMESTRALKA_BOARD_H

const int size = 10;
const int numberOfShips = 2;
//const int arrLengths[numberOfShips] = {2,3,4,5,6};
const int arrLengths[numberOfShips] = {2, 3}; //debugging

class Board {

public:
    Board();
    ~Board() = default;
    void printBoard();
    bool setShip(Battleship battleship);
    bool checkValidPlacement(Battleship battleship);
    void placeShipsRandomly();
    char attack(int x, int y);
    void attackOpponent(int x, int y, std::function<char(int, int)> func);
    char getCharFromBoard(int x, int y) {
        return x < size && x >= 0 && y < size && y >= 0 ? gameBoard[x][y] : 'Z';
    };
    bool existsShip();
    void setUsername();
    int getArrLenghts(int i) { return arrLengths[i];};
    int getNumberOfShips() {return numberOfShips;};
    int getSize() {return size;};
    std::string getUsername() {return username;};
    void setCoordinateInFogOfWar(int x, int y, char sign) {
        gameBoardFogOfWar[x][y] = sign;
    }


private:
    char gameBoard[size][size];
    char gameBoardFogOfWar[size][size];
    std::string username = "Your";
};


#endif //BATTLESHIPS_SEMESTRALKA_BOARD_H
