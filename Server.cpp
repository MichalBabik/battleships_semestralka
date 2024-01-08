
#include "Server.h"
#include "Game.h"


Server::Server(int port) : clientsReady(false) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error opening socket");
        exit(1);
    }

    bzero((char*)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    std::cout << "Server IP: " << getLocalIPAddress() << std::endl;
}

Server::~Server() {
    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }
    close(serverSocket);
}

void Server::startServerThread() {
    // Launch the server thread directly
    if (pthread_create(&serverThread, nullptr, &Server::startServerStatic, this) != 0) {
        std::cerr << "Error creating server thread" << std::endl;
        exit(1);
    }
}

void* Server::startServerStatic(void* arg) {
    Server* server = static_cast<Server*>(arg);
    server->startServer();
    return nullptr;
}

void Server::startServer() {
    waitForConnections();
}

void Server::waitForConnections() {
    int clientSocket;
    const int maxConnections = 2;

    listen(serverSocket, maxConnections);
    std::cout << "Waiting for connections..." << std::endl;

    while (clientSockets.size() < maxConnections) {
        clientLength = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientLength);
        if (clientSocket < 0) {
            perror("Error on accept");
            exit(1);
        }

        std::cout << "Connection established! Client count: " << clientSockets.size() + 1 << std::endl;

        clientSockets.push_back(clientSocket);

        // Launch a new thread to handle communication for each connected client
        pthread_t clientThread;
        if (pthread_create(&clientThread, nullptr, +[](void* obj) -> void* { return static_cast<Server*>(obj)->handleClientCommunicationStatic(obj); }, this) != 0) {
            std::cerr << "Error creating client thread" << std::endl;
            exit(1);
        }
    }
    char buffer[256];
    sendToClient(clientSockets.at(0), "Game is ready to begin!");
    sendToClient(clientSockets.at(1), "Game is ready to begin!");
    sleep(1);
    sendToClient(clientSockets.at(0), std::to_string(clientSockets.at(0)).data());
    sendToClient(clientSockets.at(1), std::to_string(clientSockets.at(1)).data());
    int x = read(clientSockets.at(0), buffer, sizeof(buffer));
    if (x < 0) {
        perror("Error reading from socket");
        exit(1);
    } else {
        memset(buffer, 0, sizeof(buffer));
        x = read(clientSockets.at(1), buffer, sizeof(buffer));
        if (x < 0) {
            perror("Error reading from socket");
            exit(1);
        }
    }
    sendToClient(clientSockets.at(0), charToString('R'));
    sendToClient(clientSockets.at(1), charToString('R'));
    clientsReady = true;
}

void* Server::handleClientCommunicationStatic(void* arg) {
    Server* server = static_cast<Server*>(arg);
    server->handleClientCommunication();
    return nullptr;
}

void Server::handleClientCommunication() {
    std::unique_lock<std::mutex> lock(mutex);

    while (true) {
        if (clientsReady) {
            for (int i = 0; i < 2; ++i) {
                int clientSocket = clientSockets[i];
                char buffer[256];
                sleep(1);
                for (int j = 0; j < 2; ++j) {
                    sendToClient(clientSockets[j], std::to_string(clientSocket).data());
                }
                memset(buffer, 0, sizeof(buffer));
                int x = read(clientSocket, buffer, sizeof(buffer));
                if (x < 0) {
                    perror("Error reading from socket");
                    exit(1);
                } else if (x == 0) {
                    std::cout << "Connection closed by the client." << std::endl;
                    break;
                } else {
                    int oClientSocket;
                    for (int otherClientSocket: clientSockets) {
                        if (otherClientSocket != clientSocket) {
                            if (strcmp(buffer, "E") == 0) {
                                //std::cout << "break" << std::endl;
                                break;
                            }
                            sendToClient(otherClientSocket, buffer);
                            oClientSocket = otherClientSocket;
                        }
                    }
                    memset(buffer, 0, sizeof(buffer));
                    x = read(oClientSocket, buffer, sizeof(buffer));
                    if (x < 0) {
                        perror("Error reading from socket");
                        exit(1);
                    } else if (x == 0) {
                        std::cout << "Connection closed by the client." << std::endl;
                        break;
                    } else {
                        sendToClient(clientSocket, buffer);
                    }
                }
            }
        }
    }
}


void Server::sendToClient(int clientSocket, const char* message) {
    send(clientSocket, message, strlen(message), 0);
}


const char* Server::charToString(char character) {
    std::string result(1, character);
    return result.c_str();
}
