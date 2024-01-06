#include "Server.h"
#include "Board.h"
#include <chrono>
#include <thread>
#include <iostream>

int main() {

    std::cout << "Welcome to the Game Networking Example!" << std::endl;

    std::cout << "Do you want to create a new game (1) or join an existing game (2)? ";
    int choice;
    std::cin >> choice;

    Board board1;
    Board board2;
    if (choice == 1) {
        // Create a new game (start as the server)
        Server server;
        server.startServerThread();

        // Wait for some time to allow the server to start
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Launch the client in the main thread

    } else if (choice == 2) {
        // Join an existing game (start as the client)

    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
    }
    return 0;
}
