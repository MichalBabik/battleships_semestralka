
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <vector>
#include <condition_variable>
#include <fcntl.h>
#include <memory>

class Server {
public:
    Server(int port);
    ~Server();

    void startServerThread();  // Launch the server thread
    static void* startServerStatic(void* arg);  // Static function for pthread_create

private:
    int port;  // Private constant variable
    int serverSocket;
    std::vector<int> clientSockets;  // Vector to store client sockets
    socklen_t clientLength;
    struct sockaddr_in serverAddress, clientAddress;
    pthread_t serverThread;  // pthread for the server thread
    std::condition_variable bothConnected;  // Condition variable for synchronization
    std::mutex mutex;  // Mutex for protecting shared data
    bool clientsReady;  // Flag indicating both clients are connected

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

    void startServer();
    void waitForConnections();
    void sendToClient(int clientSocket, const char *message);

    void handleClientCommunication();

    void *handleClientCommunicationStatic(void *arg);

    const char *charToString(char character);
};

#endif // SERVER_H
