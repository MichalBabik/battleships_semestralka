#include "Client.h"
#include "Game.h"

Client::Client(Board pBoard) {
    board = pBoard;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        error("Error opening socket");
    }

    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
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

void Client::sendGuessToServer(int guess) {
    std::string guessStr = std::to_string(guess);
    send(clientSocket, guessStr.c_str(), guessStr.length(), 0);
    std::cout << "Guess sent to server: " << guess << std::endl;
}

void Client::playGame() {

    board.setUsername();

    std::cout << "Game is in progress" << std::endl;

    Game game(board, opponentsBoard);


}

void Client::load() {

}
