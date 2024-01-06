#include <iostream>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "Board.h"
#include "Game.h"

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

    /*system("clear");

    Game game;
    game.startGame();*/

    return 0;
}