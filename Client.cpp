#include <sstream>
#include "Client.h"
#include "Game.h"

Client::Client(Board pBoard, int port) {
    board = pBoard;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        error("Error opening socket");
    }

    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, getLocalIPAddress().c_str(), &serverAddress.sin_addr) <= 0) {
        error("Invalid server address");
    }

    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        error("Error connecting to server");
    }

    std::cout << "Connected to the server!" << std::endl;

    char buffer[256];
    std::cout << "Waiting for the game to start..." << std::endl;
    int n = read(clientSocket, buffer, sizeof(buffer));
    if (n < 0) {
        error("Error reading from socket");
    } else if (n == 0) {
        std::cout << "Timeout occurred. No data received." << std::endl;
    } else {
        std::cout << "Message from server: " << buffer << std::endl;

        // Check if the message indicates that the game is ready to begin
        if (strcmp(buffer, "Game is ready to begin!") == 0) {
            std::cout << "Game is starting!" << std::endl;
            load();
            playGame();  // Start the game
        } else {
            std::cout << "Unexpected message received: " << buffer << std::endl;
        }
    }

}

Client::~Client() {
    close(clientSocket);
}

void Client::sendCoordsToServer(std::string coords) {
    send(clientSocket, coords.c_str(), coords.length(), 0);
    std::cout << "Coords sent to server: " << coords << std::endl;
}

void Client::playGame() {

    system("clear");
    std::cout << "Clients connected, please enter inputs for game initialization!" << std::endl;
    board.setUsername();

    //std::cout << "Game is in progress" << std::endl;

    Game game(board);
    //std::cin.ignore();
    while (true) {
        char buffer[256];
        int tSocket = 0;
        memset(buffer, 0, sizeof(buffer));
        int t = read(clientSocket, buffer, sizeof(buffer));
        if (t < 0) {
            error("Error reading from socket");
        } else {
            int x = 0;
            int y = 0;
            //std::cout << "Message from server: " << buffer << std::endl;
            tSocket = std::stoi(buffer);
            //std::cout << yourSocket << std::endl;
            //std::cout << tSocket << std::endl;
            if (yourSocket == tSocket) {
                std::string coords = game.attackEnemy(game.getBoard(),game.getOpponentBoard());
                if (coords == "E") {
                    sendCoordsToServer(charToString('E'));
                    std::cout << "You have left the game" << std::endl;
                    break;
                }
                sendCoordsToServer(coords);
                std::istringstream iss(coords);
                iss >> x >> y;
                memset(buffer, 0, sizeof(buffer));
                int  n = read(clientSocket, buffer, sizeof(buffer));

                system("clear");

                if (n < 0) {
                    error("Error reading from socket");
                } else {
                    //std::cout << "Message from server: " << buffer << std::endl;

                    if (strcmp(buffer, "V") == 0) {
                        std::cout << "Congratulations! You won!" << std::endl;
                        break;  // Exit the loop since the game is over
                    } else if (strcmp(buffer, " ") == 0) {
                        std::cout << "Your missile hit water..." << std::endl;
                    } else if (strcmp(buffer, "X") == 0) {
                        std::cout << "You hit enemy battleship" << std::endl;
                        std::cout << x << y << std::endl;
                        game.getBoard().setCoordinateInFogOfWar(x, y, 'X');
                    } else {
                        std::cout << "Unexpected message received: " << buffer << std::endl;
                    }
                }

            } else {
                int x = 0;
                int y = 0;
                char r;
                game.getBoard().printBoard();
                std::cout << "Please wait - opponent turn in progress..." << std::endl;
                memset(buffer, 0, sizeof(buffer));
                int n = read(clientSocket, buffer, sizeof(buffer));

                if (n < 0) {
                    error("Error reading from socket");
                } else {
                    //std::cout << "Message from server: " << buffer << std::endl;
                    std::istringstream iss(buffer);

                    if(iss >> x >> y) {
                        r = game.getBoard().attack(x, y);
                        if (!game.getBoard().existsShip()){
                            send(clientSocket, charToString('V'), strlen(charToString('V')), 0);
                            std::cout << "You lost" << std::endl;
                            break;
                        } else {
                            send(clientSocket, charToString(r), strlen(charToString(r)), 0);
                        }
                    } else {
                        std::cout << "You have won! Opponent has left the game." << std::endl;
                        break;
                    }

                }
            }
        }
    }
}

void Client::load() {
    char buffer[256];
    int n = read(clientSocket, buffer, sizeof(buffer));
    if (n < 0) {
        error("Error reading from socket");
    } else if (n == 0) {
        std::cout << "Timeout occurred. No data received." << std::endl;
    } else {
        yourSocket = std::stoi(buffer);
        std::cout << "You are player number: " << buffer << std::endl;
    }
}

const char* Client::charToString(char character) {
    char* result = new char[2];
    result[0] = character;
    result[1] = '\0';  // Null-terminate the string
    return result;
}
