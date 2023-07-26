#include "User.hpp"

using namespace std;

User::User(){

}

User::User(string username, string password, double availableSize, string admin):
    username(username), password(password), availableSize(availableSize), admin(admin == "true"){
}

string User::getUsername(){
    return username;
}

string User::getPassword(){
    return password;
}

int User::getAvailableSize(){
    return availableSize;
}

bool User::isAdmin(){
    return admin;
}

void User::reduceAvailableSize(double size){
    availableSize -= size;
}




