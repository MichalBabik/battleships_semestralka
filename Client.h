#ifndef BATTLESHIPS_SEMESTRALKA_CLIENT_H
#define BATTLESHIPS_SEMESTRALKA_CLIENT_H

#include <fcntl.h>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <algorithm>
#include <cctype>
#include <cstring>
#include "Board.h"

class Client {
public:
    Client(Board board, int port);
    ~Client();

    void playGame();
    void setOpponentsBoard(Board pOpponentsBoard){opponentsBoard = pOpponentsBoard;};

private:
    int port;
    int clientSocket;
    struct sockaddr_in serverAddress;
    int yourSocket;
    Board board;
    Board opponentsBoard;

    void error(const char *msg) {
        perror(msg);
        exit(1);
    }

    std::string getLocalIPAddress() {
        char hostbuffer[256];
        if (gethostname(hostbuffer, sizeof(hostbuffer)) == -1) {
            error("Error getting hostname");
        }

        struct hostent *host_entry;
        host_entry = gethostbyname(hostbuffer);
        if (host_entry == nullptr) {
            error("Error getting host entry");
        }

        char *ip_buffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
        if (ip_buffer == nullptr) {
            error("Error converting IP address");
        }

        return std::string(ip_buffer);
    }

    void sendCoordsToServer(std::string coords);

    void load();

    const char *charToString(char character);
};

#endif //BATTLESHIPS_SEMESTRALKA_CLIENT_H
