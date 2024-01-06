#include "Board.h"
#include <string>
#include <iostream>

#ifndef BATTLESHIPS_SEMESTRALKA_GAME_H
#define BATTLESHIPS_SEMESTRALKA_GAME_H

class Game {

public:
    Game(Board pBoard, Board opponentsBoard);
    ~Game() = default;
    void initializer();
    void customDistribution(Board& board);
    void startGame();
    void attackEnemy(Board& boardAttacker, Board& boardAttacked);
    bool getIsEnd() {return isEnd;};
    bool getTurn() {return turn;};
    Board getBoard() {return board;};

private:
    Board board;
    Board opponentsBoard;
    bool turn;
    bool isEnd;
};


#endif //BATTLESHIPS_SEMESTRALKA_GAME_H
