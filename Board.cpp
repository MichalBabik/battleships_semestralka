#include <iostream>
#include "Board.h"

Board::Board() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            gameBoard[i][j] = '#';
            gameBoardFogOfWar[i][j] = '#';
        }
    }
}

void Board::printBoard() {

    std::cout << "************************************** Battleships ******************************************\n";
    // Print the header for both boards
    std::cout << username <<" Board";
    // Add spacing to align the "Battleships" headline
    for (int i = 0; i < 61; ++i) {
        std::cout << " ";
    }
    std::cout << "Opponents board\n";
    // Horizontal numbering for both boards
    std::cout << "  ";
    for (int j = 0; j < size; ++j) {
        std::cout << j << " ";
    }
    // Separator with 50 spaces
    for (int i = 0; i < 50; ++i) {
        std::cout << " ";
    }
    std::cout << "  ";

    for (int j = 0; j < size; ++j) {
        std::cout << j << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < size; ++i) {
        // Vertical numbering and content for the first board
        std::cout << i << " ";
        for (int j = 0; j < size; ++j) {
            std::cout << gameBoard[j][i] << " ";
        }
        // Separator with 50 spaces
        for (int k = 0; k < 50; ++k) {
            std::cout << " ";
        }
        // Vertical numbering and content for the second board (Fog of War)
        std::cout << i << " ";
        for (int j = 0; j < size; ++j) {
            std::cout << gameBoardFogOfWar[j][i] << " ";
        }
        std::cout << "\n";
    }
}

char Board::attack(int x, int y) {
    if (x >= 0 && x < size && y < size && y >= 0) {
        system("clear");
        if (gameBoard[x][y] == ' ' || gameBoard[x][y] == 'X') {
            std::cout << "You have already attacked this coordinate!" << std::endl;
            return  gameBoard[x][y];
        }
        if (gameBoard[x][y] == '#') {
            gameBoard[x][y] = ' ';
            std::cout << "Missile hit coordinates [" << x << "," << y << "] luckily there was only water!" << std::endl;
            return ' ';
        }
        if (gameBoard[x][y] == 'O') {
            gameBoard[x][y] = 'X';
            std::cout << "Battleship was hit by a missile at coordinates [" << x << "," << y << "]!" << std::endl;
            return 'X';
        }
    } else {
        std::cout << "Wrong coordinates!" << std::endl;
        return 'Z';
    }
}

void Board::attackOpponent(int x, int y, std::function<char(int, int)> func) {
    if (x >= 0 && x < size && y < size && y >= 0) {
        std::cout << x << " " << y << std::endl;
        gameBoardFogOfWar[x][y] = (func)(x, y);
    } else {
        std::cout << "Wrong coordinates!" << std::endl;
    }
}

void Board::placeShipsRandomly() {
    for (int i = 0; i < getNumberOfShips(); ++i) {
        bool shipPlaced = false;

        while (!shipPlaced) {
            int x = std::rand() % size;
            int y = std::rand() % size;
            int randOrientation = std::rand() % 4;
            char orientation;
            switch (randOrientation) {
                case 0:
                    orientation = 'N';
                    break;
                case 1:
                    orientation = 'S';
                    break;
                case 2:
                    orientation = 'W';
                    break;
                case 3:
                    orientation = 'E';
                    break;
                default:
                    orientation = 'N';
                    break;
            }
            Battleship ship(x, y, arrLengths[i], orientation);
            shipPlaced = setShip(ship);
        }
    }
}

bool Board::setShip(Battleship battleship) {
    if (checkValidPlacement(battleship)) {
        switch (battleship.getOrientation()) {
            case 'W':
                //x-
                for (int i = battleship.getX() ; i > battleship.getX() - battleship.getLength(); --i) {
                    gameBoard[i][battleship.getY()] = 'O';
                }
                break;
            case 'E':
                //x+
                for (int i = battleship.getX() ; i < battleship.getX() + battleship.getLength(); ++i) {
                    gameBoard[i][battleship.getY()] = 'O';
                }
                break;
            case 'S':
                //y+
                for (int i = battleship.getY() ; i < battleship.getY() + battleship.getLength(); ++i) {
                    gameBoard[battleship.getX()][i] = 'O';
                }
                break;
            case 'N':
                //y-
                for (int i = battleship.getY() ; i > battleship.getY() - battleship.getLength() ; --i) {
                    gameBoard[battleship.getX()][i] = 'O';
                }
                break;
            default:
                std::cout << "Wrong orientation of the battleship!" << std::endl;
                break;
        }
        system("clear");
        std::cout << "Battleship successfully placed!" << std::endl;
        return true;
    }
    return false;
}

bool Board::checkValidPlacement(Battleship battleship) {

    if (battleship.getX() < 0 || battleship.getY() < 0 || battleship.getX() >= size || battleship.getY() >= size) {
        std::cout << "Wrong coordinates!" << std::endl;
        return false;
    }

    switch (battleship.getOrientation()) {
        case 'W':
            //x-
            if (battleship.getX() - battleship.getLength() + 1 < 0) {
                std::cout << "Not enough space in that direction!" << std::endl;
                return false;
            }

            for (int i = battleship.getX() ; i > battleship.getX() - battleship.getLength(); --i) {
                if (gameBoard[i][battleship.getY()] == 'O') {
                    std::cout << "Another battleship in the way (coordinate[" << i << ", " <<  battleship.getY() << "])!" << std::endl;
                    return false;
                }
            }
            break;
        case 'E':
            //x+
            if (battleship.getX() + battleship.getLength() > size ) {
                std::cout << "Not enough space in that direction!" << std::endl;
                return false;
            }

            for (int i = battleship.getX() ; i < battleship.getX() + battleship.getLength(); ++i) {
                if (gameBoard[i][battleship.getY()] == 'O') {
                    std::cout << "Another battleship in the way (coordinate[" << i << ", " <<  battleship.getY() << "])!" << std::endl;
                    return false;
                }
            }
            break;
        case 'S':
            //y+
            if (battleship.getY() + battleship.getLength() > size ) {
                std::cout << "Not enough space in that direction!" << std::endl;
                return false;
            }

            for (int i = battleship.getY() ; i < battleship.getY() + battleship.getLength(); ++i) {
                if (gameBoard[battleship.getX()][i] == 'O') {
                    std::cout << "Another battleship in the way (coordinate[" << battleship.getX() << ", " <<  i << "])!" << std::endl;
                    return false;
                }
            }
            break;
        case 'N':
            //y-
            if (battleship.getY() - battleship.getLength() + 1 < 0) {
                std::cout << "Not enough space in that direction!" << std::endl;
                return false;
            }

            for (int i = battleship.getY() ; i > battleship.getY() - battleship.getLength() ; --i) {
                if (gameBoard[battleship.getX()][i] == 'O') {
                    std::cout << "Another battleship in the way (coordinate[" << battleship.getX() << ", " <<  i << "])!" << std::endl;
                    return false;
                }
            }
            break;
        default:
            std::cout << "Wrong orientation of the battleship!" << std::endl;
            return false;
    }
    return true;
}

bool Board::existsShip() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (gameBoard[i][j] == 'O') {
                return true;
            }
        }
    }
    return false;
}

void Board::setUsername() {
    std::cout << "Enter Username!" << std::endl;
    std::cin >> username;
}



