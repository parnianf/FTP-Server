#ifndef _COMMAND_HANDLER_H_
#define _COMMAND_HANDLER_H_



#include <vector>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <map>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <fstream>




#include "User.hpp"
#include "UserManager.hpp"
#include "JsonParser.hpp"
#include "Logger.hpp"

struct Request{
    std::string command;
    std::vector<std::string> args;
};

class CommandHandler{
public:
    CommandHandler();
    CommandHandler(JsonParser jsonParser, Logger* logger, int data_fd);
    std::string run(std::string input);
private:
    Logger* logger;
    int dataFd;
    std::string directory, clientDirectory;
    UserManager userManager;
    JsonParser jsonParser;
    std::string userHandler(std::string username);
    std::string passHandler(std::string pass);
    std::string execCommand(std::string command, std::vector<std::string> arguments);
    std::string pwdHandler(std::vector<std::string> arguments);
    std::string mkdHandler(std::vector<std::string> arguments);
    std::string deleHandler(std::vector<std::string> arguments);
    std::string lsHandler();
    std::string cwdHandler(std::vector<std::string> arguments);
    std::string renameHandler(std::vector<std::string> arguments);
    void retrHandler(std::vector<std::string> arguments);
    std::string helpHandler(); 
    std::string quitHandler(); 
};

#endif