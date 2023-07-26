#ifndef _JSON_PARSER_H_
#define _JSON_PARSER_H_ 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "User.hpp"
#include "Json.hpp"


#define USERS_JSON "users"
#define USER "user"
#define PASSWORD "password"
#define SIZE_JSON "size"
#define ADMIN_JSON "admin"
#define FILES_JSON "files"
#define COMMAND_PORT_JSON "commandChannelPort"
#define DATA_PORT_JSON "dataChannelPort"


using json = nlohmann::json;

class JsonParser
{
public:
    JsonParser();
    JsonParser(std::string config_file_path);
    std::vector<User> getUsers();
    std::vector<std::string> getPrivilegedFiles();
    int getCommandChannelPort();
    int getDataChannelPort();
    bool isPrivileged(const std::string file);
private:
    std::string configFilePath;
    std::vector<User> users;
    std::vector<std::string> privilegedFiles;
    int commandChannelPort, dataChannelPort;
};

#endif