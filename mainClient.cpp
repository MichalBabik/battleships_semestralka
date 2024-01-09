#include <iostream>
#include <thread>
#include "Board.h"
#include "Game.h"
#include "Client.h"

int main(int argc, char** argv) {
    srand(time(0));

    std::cout << "Welcome to battleships game!" << std::endl;

    /*std::cout << "Do you want to create a new game (1) or join an existing game (2)? ";
    int choice;


    std::cin >> choice;*/
    int port = 0;
    bool set = false;

    Board board1;
    Board board2;



    while (!set) {
        if (port >= 1024 && port <= 65535) {
            set = true;
        } else {
            std::cout << "Enter port number : " << std::endl;
            std::cin >> port;
        }

    }

    Client client(board1, port);
    client.setOpponentsBoard(board2);

    return 0;
}
