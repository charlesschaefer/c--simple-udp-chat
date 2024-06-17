#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080


int server() {

    int serSockDes, len, readStatus;
    struct sockaddr_in serAddr, cliAddr;
    char buff[1024] = {0};
    char msg[] = "Hello to you too!!!\n";

    //creating a new server socket
    if((serSockDes = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation error...\n");
        exit(-1);
    }

    //binding the port to ip and port
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(PORT);
    serAddr.sin_addr.s_addr = INADDR_ANY;

    if((bind(serSockDes, (struct sockaddr*)&serAddr, sizeof(serAddr))) < 0) {
        perror("binding error...\n");
        exit(-1);
    }

    printf("Everything ok, starting to receive messages\n");
    std::map<int, struct sockaddr_in> clients;
    std::map<int, struct sockaddr_in>::iterator iter;


    while (true) {
        readStatus = recvfrom(serSockDes, buff, 1024, 0, (struct sockaddr*)&cliAddr, (socklen_t*)&len);
        //buff[readStatus] = '\n';
        buff[readStatus] = '\0';

        printf("Received message %s from client %d\n", buff, cliAddr.sin_port);

        if (!clients.empty()) {
            iter = clients.find(cliAddr.sin_port);
            // checks if the client is not in the map
            if (iter == clients.end()) {
                clients[cliAddr.sin_port] = cliAddr;
            }
        } else {
            clients[cliAddr.sin_port] = cliAddr;
        }

        iter = clients.begin();
        while (iter != clients.end()) {
            printf("\nSending %ld bytes of a message from client %d to client %d\n", sizeof(buff), cliAddr.sin_port, iter->second.sin_port);
            //if (iter->first != cliAddr.sin_port) {
                sendto(serSockDes, buff, strlen(buff), 0, (struct sockaddr*)&iter->second, sizeof(iter->second));
            //}
            iter++;
        } 
    }

    return 0;
}

int client() {
    int cliSockDes, readStatus, len;
    struct sockaddr_in serAddr;
    char msg[] = "Hello!!!\n";
    char buff[1024] = {0};

    //create a socket
    if((cliSockDes = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation error...\n");
        exit(-1);
    }

    //server socket address
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(PORT);
    serAddr.sin_addr.s_addr = INADDR_ANY;

    char buffer[80];
    printf("Message to send: \n");
    fflush (stdout);
    scanf ("%79s",buffer);
    sendto(cliSockDes, buffer, strlen(buffer), 0, (struct sockaddr*)&serAddr, sizeof(serAddr));

    while (true) {
        readStatus = recvfrom(cliSockDes, buff, 1024, 0, (struct sockaddr*)&serAddr, (socklen_t*)&len);
        buff[readStatus] = '\0';
        std::cout<<buff;
    }

    return 0;
}


int main(int argc, char *argv[]) {
    //Server server = Server(HOST, PORT);

    if (argc <= 1) {
        printf("Usage: udp-chat {option}, where {option} can be server or client\n");
        exit(-1);
    }

    if (std::string(argv[1]) == "server") {
        printf("Opening server\n");
        server();
    } else if (std::string(argv[1]) == "client") {
        printf("Opening client\n");
        client();
    } else {
        printf("Not correct argument\n");
    }

    return 0;
}

/* #include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    printf ("Guess my favorite fruit? \n");
    if (std::string(argv[1]) == "apple") {
        puts ("Correct answer!");
    }
  return 0;
} */