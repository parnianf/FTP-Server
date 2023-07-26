#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <string>

class User{
private:
    std::string username;
    std::string password;
    double availableSize;
    bool admin;

public:
    User();
    User(std::string username, std::string password, double availableSize, std::string admin);
    std::string getUsername();
    std::string getPassword();
    int getAvailableSize();
    bool isAdmin();
    void reduceAvailableSize(double size);
};

#endif
