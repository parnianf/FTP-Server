#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <chrono>
#include <ctime> 
#include <string>
#include <fstream>
#include <iostream>

class Logger {
public:
    Logger();
    Logger(std::string path);
    void record(std::string message);

private:
    std::string path;
};

#endif
