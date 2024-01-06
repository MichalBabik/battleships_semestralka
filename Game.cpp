#include <sstream>
#include"Game.h"

Game::Game() {
    initializer();
}

void Game::initializer() {
    std::string options = " ";
    while (options != "R" && options != "C" ) {
        std::cout << "Enter [R] if you want randomly placed battleships or [C] for custom layout of battleships." << std::endl;
        std::cin >> options;
        if (options == "R" || options == "C") {
            break;
        } else {
            std::cout << "Wrong input please try again!" << std::endl;
        }
    }

    if (options == "R") {
        board1.placeShipsRandomly();
        board2.placeShipsRandomly();
    }
    if (options =="C") {
        std::cin.ignore();
        customDistribution(board1);
        customDistribution(board2);
    }
}

void Game::customDistribution(Board& board) {
    for (int i = 0; i < board.getNumberOfShips(); ++i) {
        board.getArrLenghts(i);
        bool isPlaced = false;
        while (!isPlaced) {
            std::cout << "Please select coordinates and orientation for your battleship with length " << board.getArrLenghts(i) << std::endl;
            std::cout << "Please enter input in this format: x y orientation (for example: 1 2 E)" << std::endl;
            std::string input;
            std::getline(std::cin, input);
            std::istringstream iss(input);

            int x;
            int y;
            char orientation;

            if (iss >> x >> y >> orientation) {
                Battleship ship(x, y, board.getArrLenghts(i),orientation);
                isPlaced = board.setShip(ship);
            } else {
                std::cerr << "Invalid input format!" << std::endl;
            }
        }

        board.printBoard();
    }
    std::cout << "Board successfully initialized " << std::endl;
}

void Game::startGame() {
    std::cin.ignore();
    isEnd = false;
    turn = true;
    while (!isEnd) {
        if (turn) {
            attackEnemy(board1, board2);
            if (!board2.existsShip()) {
                std::cout << board1.getUsername() << " has won!" << std::endl;
                isEnd = true;
            }
        } else {
            attackEnemy(board2, board1);
            if (!board1.existsShip()) {
                std::cout << board2.getUsername() << " has won!" << std::endl;
                isEnd = true;
            }
        }
    }
}

void Game::attackEnemy(Board& boardAttacker, Board& boardAttacked) {
    bool attacked = false;
    while (!attacked) {
        boardAttacker.printBoard();
        std::string coordinates;
        std::cout << "Enter coordinates where you want to fire a missile!" << std::endl;;
        std::getline(std::cin, coordinates);
        std::istringstream iss(coordinates);
        int x;
        int y;
        if (iss >> x >> y) {
            if (x >= 0 && x < boardAttacked.getSize() && y >= 0 && y < boardAttacked.getSize() ) {
                if (boardAttacked.getCharFromBoard(x, y) == 'O' || boardAttacked.getCharFromBoard(x, y) == '#') {
                    auto attackFunction = [&](int x, int y) { return boardAttacked.attack(x, y); };
                    boardAttacker.attackOpponent(x, y, attackFunction);
                    attacked = true;
                    turn = !turn;
                } else {
                    std::cout << "You have already fired at this coordinate!" << std::endl;;
                }
            } else {
                std::cout << "Entered coordinates are invalid!" << std::endl;;
            }
        } else {
            std::cerr << "Invalid input format!" << std::endl;
        }
    }
}





