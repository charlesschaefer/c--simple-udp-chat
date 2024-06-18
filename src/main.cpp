#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "server.h"
#include "client.h"

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        printf("Usage: udp-chat {option}, where {option} can be server or client\n");
        exit(-1);
    }

    if (std::string(argv[1]) == "server") {
        printf("Opening server\n");
        Server server = Server(2222);
        server.startServer();
    } else if (std::string(argv[1]) == "client") {
        printf("Opening client\n");
        Client client = Client(2222);
        client.receive();
    } else {
        printf("Incorrect argument\n");
    }

    return 0;
}
