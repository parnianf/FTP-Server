#include "Client.hpp"

#include <fstream>
#include <sstream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

Client::Client(){
}

int connectServer(int port){
    int fd;
    struct sockaddr_in serverAddress;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
        printf("Error in connecting to server\n");
    }
    return fd;
}

void Client::readPorts(string configPath){

    ifstream file(configPath);
    json configJson;
    file >> configJson;
    commandChannelPort = configJson[COMMAND_PORT_JSON];
    dataChannelPort = configJson[DATA_PORT_JSON];

}

void Client::run() {

    int commandFd = connectServer(commandChannelPort);
    int dataFd = connectServer(dataChannelPort);

    char commandOutput[100000] = {0};
    char dataOutput[100000] = {0};
    while (true) {
        // Receive command from command line.
        char command[MAX_INPUT_SIZE];
        memset(command, 0, MAX_INPUT_SIZE);
        cin.getline(command, MAX_INPUT_SIZE);

        // Send command to server.
        send(commandFd, command, MAX_INPUT_SIZE, 0);

        // Receive command output from server.
        memset(commandOutput, 0, sizeof commandOutput);
        recv(commandFd, commandOutput, sizeof(commandOutput), 0);
        cout << commandOutput << endl;
        
        stringstream retrCmd(command);
        vector<string> retr;
        string content;
        while(retrCmd >> content){
            retr.push_back(content);
        }

        //In case of download command(retr) we write the recieved content into a file.
        if(retr[0] == "retr"){
            if(retr.size() != 2){
                cout<<"Wrong File Name"<<endl;
            }

            //Reveive data output from server.
            memset(dataOutput, 0, sizeof dataOutput);
            recv(dataFd, dataOutput, sizeof(dataOutput), 0);
            cout << "File content: " <<endl<< dataOutput << endl;
            //write content of downloaded file.
            ofstream downloadedFile(retr[1]);
            downloadedFile << dataOutput;
            downloadedFile.close();
        }
    }

}

