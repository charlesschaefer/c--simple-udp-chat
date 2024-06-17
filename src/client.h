class Client {
    private:
        int server;
        int serverPort;
    
    public:
        Client(int serverPort) {
            //create a socket
            if((server = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                perror("socket creation error...\n");
                exit(-1);
            }

            this->serverPort = serverPort;

            receive();
        }

        void receive() {
            struct sockaddr_in serverAddr;

            //server socket address
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_port = htons(serverPort);
            serverAddr.sin_addr.s_addr = INADDR_ANY;

            char buffer[80];
            printf("Message to send: \n");
            fflush (stdout);
            scanf ("%79s", buffer);
            sendto(server, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

            char buff[1024] = {0};
            int len, readStatus;
            
            printf("Starting to receive messages from server.\n");
            while (true) {
                readStatus = recvfrom(server, buff, 1024, 0, (struct sockaddr*)&serverAddr, (socklen_t*)&len);
                buff[readStatus] = '\0';
                std::cout<<buff;
            }

        }
};