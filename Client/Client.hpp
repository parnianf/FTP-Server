#ifndef CLIENT_H_
#define CLIENT_H_

#include "Json.hpp"

#define COMMAND_PORT_JSON "commandChannelPort"
#define DATA_PORT_JSON "dataChannelPort"
#define MAX_INPUT_SIZE 1024
using json = nlohmann::json;

class Client {
public:
    Client();
    void run();
    void readPorts(std::string configPath);
private:
    int commandChannelPort, dataChannelPort;
};

#endif
