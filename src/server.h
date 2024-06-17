
#define HOST "127.0.0.1"
#define PORT 2222


class Server {

    public:
        std::vector<struct sockaddr_in *> clients;
        // file descriptor to the server socket
        int server;

        Server(char host[], int port);
}

