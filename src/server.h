#include <string>

class Server {

    private:
        std::map<int, struct sockaddr_in> clients;
        // file descriptor to the server socket
        int server;
        int serverPort;
    
    public:
        Server(int serverPort) {
            // creates a UDP ipv4 socket
            if((server = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                perror("socket creation error...\n");
                exit(-1);
            }

            this->serverPort = serverPort;

        }
        void startServer() {
            struct sockaddr_in serverAddr, clientAddr;
            int len, readStatus;
            char buff[1024] = {0};

            //binding the port to ip and port
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_port = htons(serverPort);
            serverAddr.sin_addr.s_addr = INADDR_ANY;

            if((bind(server, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) < 0) {
                perror("binding error...\n");
                exit(-1);
            }

            printf("Everything ok, starting to receive messages\n");

            std::map<int, struct sockaddr_in>::iterator iter;
            while (true) {
                readStatus = recvfrom(server, buff, 1024, 0, (struct sockaddr*)&clientAddr, (socklen_t*)&len);
                buff[readStatus] = '\0';

                printf("Received message %s from client %d\n", buff, clientAddr.sin_port);

                // adds the client in the list to be notified
                if (!clients.empty()) {
                    iter = clients.find(clientAddr.sin_port);
                    // checks if the client is not in the map
                    if (iter == clients.end()) {
                        clients[clientAddr.sin_port] = clientAddr;
                    }
                } else {
                    clients[clientAddr.sin_port] = clientAddr;
                }

                iter = clients.begin();
                while (iter != clients.end()) {
                    printf("\nSending %ld bytes of a message from client %d to client %d\n", sizeof(buff), clientAddr.sin_port, iter->second.sin_port);
                    //if (iter->first != clientAddr.sin_port) {
                        sendto(server, buff, strlen(buff), 0, (struct sockaddr*)&iter->second, sizeof(iter->second));
                    //}
                    iter++;
                }
            }
        }

};

