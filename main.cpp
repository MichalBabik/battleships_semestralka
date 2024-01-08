#include <iostream>
#include <thread>
#include "Board.h"
#include "Game.h"
#include "Server.h"
#include "Client.h"

int main(int argc, char** argv) {
    srand(time(0));

    std::cout << "Welcome to battleships game!" << std::endl;

    std::cout << "Do you want to create a new game (1) or join an existing game (2)? ";
    int choice;
    int port = 0;
    bool set = false;
    std::cin >> choice;

    Board board1;
    Board board2;
    if (choice == 1) {

        while (!set) {
            if (port >= 1024 && port <= 65535) {
                set = true;
            } else {
                std::cout << "Enter port number : " << std::endl;
                std::cin >> port;
            }
        }

        Server server(port);
        server.startServerThread();

        std::this_thread::sleep_for(std::chrono::seconds(2));

        Client client(board1, port);
        client.setOpponentsBoard(board2);

    } else if (choice == 2) {

        while (!set) {
            if (port >= 1024 && port <= 65535) {
                set = true;
            } else {
                std::cout << "Enter port number : " << std::endl;
                std::cin >> port;
            }

        }

        Client client(board2, port);
        client.setOpponentsBoard(board1);
    } else {
            std::cout << "Invalid choice. Exiting." << std::endl;
    }
    return 0;
}