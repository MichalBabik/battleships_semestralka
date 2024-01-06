#include <iostream>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <thread>
#include "Board.h"
#include "Game.h"
#include "Server.h"
#include "Client.h"

/*::string getMyIP(){
    const char* google_dns_server = "8.8.8.8";
    int dns_port = 53;
    struct sockaddr_in serv;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        return "Unable to create a socket";
    }
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(google_dns_server);
    serv.sin_port = htons(dns_port);
    if (connect(sock, (const struct sockaddr*)&serv, sizeof(serv)) < 0){
        return "Connection error";
    }
    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    int err = getsockname(sock, (struct sockaddr*)&name, &namelen);
    char buffer[80];
    const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, 80); //zistenie ip adresy
    if(p != NULL){
        return buffer;
    }
    close(sock);
    return strerror(errno);
}*/

int main(int argc, char** argv) {
    srand(time(0));

    std::cout << "Welcome to battleships game!" << std::endl;

    std::cout << "Do you want to create a new game (1) or join an existing game (2)? ";
    int choice;
    std::cin >> choice;

    Board board1;
    Board board2;
    if (choice == 1) {

        Server server;
        server.startServerThread();


        std::this_thread::sleep_for(std::chrono::seconds(2));


        Client client(board1);
        client.setOpponentsBoard(board2);
    } else if (choice == 2) {

        Client client(board2);
        client.setOpponentsBoard(board1);
    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
    }
    return 0;

    /*system("clear");
    srand(time(0));
    Game game;
    game.startGame();*/

}