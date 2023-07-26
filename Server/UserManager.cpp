#include "UserManager.hpp"

using namespace std;

UserManager::UserManager(){
    loggedIn = false;
    foundUser = false; 
}

bool UserManager::isLoggedIn(){
    return loggedIn;
}

User UserManager::getUser(){
    return user;
}

bool UserManager::login(string pass){
    if(loggedIn){
        throw string(ERROR);
    }
    if(!foundUser){
        throw string(BAD_SEQUENCE);
    }
    if(pass == user.getPassword()){
        loggedIn = true;
        return true;
    }
    else
        throw string(INVALID_USER_PASS);
}

string UserManager::checkUser(vector<User> users, string username){
    if(loggedIn)
        throw string(ERROR);
    if(foundUser){
        foundUser = false;
    }
    for(auto u : users){
        if(username.compare(u.getUsername()) == 0){
            user = u;
            foundUser = true;
            break;
        }
    }
    if(foundUser)
        return string(USERNAME_ACCEPTED);
    
    else 
        throw string(INVALID_USER_PASS);
}

bool UserManager::quit(){
    if(!loggedIn)
        throw string(ERROR);    
    foundUser = false;
    loggedIn = false;
    return true;
}