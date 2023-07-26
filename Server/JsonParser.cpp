#include "JsonParser.hpp"

using namespace std;

JsonParser::JsonParser(){
    
}

JsonParser::JsonParser(string configFilePath) : configFilePath(configFilePath){
    ifstream file(configFilePath);
    json configFile;
    file >> configFile;
    for (auto& user: configFile[USERS_JSON]){
        User newUser = User(
            user[USER].get<string>(),
            user[PASSWORD].get<string>(),
            stoi(user[SIZE_JSON].get<string>()),
            user[ADMIN_JSON].get<string>());
        users.push_back(newUser);
    }
    for (auto& file: configFile[FILES_JSON])
        privilegedFiles.push_back(file.get<string>());

    commandChannelPort = configFile[COMMAND_PORT_JSON];
    dataChannelPort = configFile[DATA_PORT_JSON];
}

bool JsonParser::isPrivileged(const string file){
    for(string f : privilegedFiles){
        if (file == f){
            return true;
        }
    }
    return false;
}

int JsonParser::getCommandChannelPort(){
    return commandChannelPort;
}

int JsonParser::getDataChannelPort(){
    return dataChannelPort;
}

vector<User> JsonParser::getUsers(){
    return users;
}

vector<string> JsonParser::getPrivilegedFiles(){
    return privilegedFiles;
}