#include "Server.hpp"
#define MAX_CONNECTIONS 10
using namespace std;

Server::Server(string configPath){ //constructor
    logger = new Logger(LOG_FILE);
    jsonParser = JsonParser(configPath);
}

int Server::setupSocket(int port){ //setting up a socket
    struct sockaddr_in serverAddress;

    int serverFd = socket(AF_INET, SOCK_STREAM, 0); // TCP connection
    int opt = 1;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(int));
    bind(serverFd, (struct sockaddr*)& serverAddress, sizeof(serverAddress));
    listen(serverFd, MAX_CONNECTIONS); // listen to maximum 10 connections.
    return serverFd;
}


void Server::start() {

    int commandFd = setupSocket(jsonParser.getCommandChannelPort());//for server
    int data_fd = setupSocket(jsonParser.getDataChannelPort());

    fd_set masterSet, workingSet;
    FD_ZERO(&masterSet);
    FD_SET(commandFd, &masterSet);
    int maxFd = commandFd;
    char buffer[1024] = {0};

    cout << "Server is running..." << endl;
    while (true) {
        workingSet = masterSet;
        select(maxFd + 1, &workingSet, NULL, NULL, NULL);

        for (int fd = 0; fd <= maxFd; fd++) {
            if (FD_ISSET(fd, &workingSet)) {
                if (fd == commandFd) { //new client
                    int commandSocket = accept(commandFd, NULL, NULL);
                    int dataSocket = accept(data_fd, NULL, NULL);
                    
                    commandHandlers[commandSocket] = CommandHandler(jsonParser, logger, dataSocket);
                    FD_SET(commandSocket, &masterSet);
                    if (commandSocket > maxFd)
                        maxFd = commandSocket;
                }
                else {// client sending message
                    memset(buffer, 0, sizeof buffer);
                    int bytesReceived = recv(fd, buffer, sizeof(buffer), 0);
                    if (bytesReceived == 0){
                        close(fd);
                        FD_CLR(fd, &masterSet);
                    }
                    else {
                        string output = commandHandlers[fd].run(buffer);
                        send(fd , output.c_str() , output.size() , 0);
                    }
                }
            }
        }
    }
}

