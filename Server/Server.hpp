#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/socket.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "CommandHandler.hpp"
#include "JsonParser.hpp"
#include "UserManager.hpp"
#include "Logger.hpp"

#define LOG_FILE "log.txt"

class Server {
public:
    Server(std::string configPath);
    int setupSocket(int port);
    void start();

private:
    Logger* logger;
    std::map<int, CommandHandler> commandHandlers; //commandFd to commandHandler (based on client socket)
    JsonParser jsonParser;
};

#endif
