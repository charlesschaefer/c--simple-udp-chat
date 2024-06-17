#include "server.h"

Server::Server(char host[], int port) {
    // creates a UDP ipv4 socket
    server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server < 0) {
        perror("Couldn't create a socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;


    int bound = bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (bound < 0) {
        perror(sprintf("Couldn't bind to localhost:%d", port));
        exit(EXIT_FAILURE);
    }
}

