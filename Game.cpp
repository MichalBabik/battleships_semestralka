#include <sstream>
#include"Game.h"

Game::Game(Board pBoard, Board pOpponentsBoard) {
    board = pBoard;
    opponentsBoard = pOpponentsBoard;

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
        board.placeShipsRandomly();
        system("clear");
        std::cout << "Battleships randomly placed!" << std::endl;
    }
    if (options == "C") {
        std::cin.ignore();
        customDistribution(board);
    }
}

void Game::customDistribution(Board& pBoard) {
    system("clear");
    pBoard.printBoard();
    for (int i = 0; i < pBoard.getNumberOfShips(); ++i) {
        pBoard.getArrLenghts(i);
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
                system("clear");
                Battleship ship(x, y, pBoard.getArrLenghts(i),orientation);
                isPlaced = pBoard.setShip(ship);
            } else {
                system("clear");
                std::cerr << "Invalid input format!" << std::endl;
            }
            pBoard.printBoard();
        }

    }
    std::cout << "Board successfully initialized " << std::endl;
}

std::string Game::attackEnemy(Board& boardAttacker, Board& boardAttacked) {
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

                    /*turn = !turn;*/
                    attacked = true;

                    return coordinates;

                } else {
                    system("clear");
                    std::cout << "You have already fired at this coordinate! (Choose different coordinates!)" << std::endl;;
                }
            } else {
                system("clear");
                std::cout << "Entered coordinates are invalid! (Choose different coordinates!)" << std::endl;;
            }
        } else {
            system("clear");
            std::cerr << "Invalid input format! (Choose different coordinates!)" << std::endl;
        }
    }
}





