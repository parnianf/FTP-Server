#ifndef _USERMANAGER_H_
#define _USERMANAGER_H_

#include "User.hpp"
#include <string.h>
#include <vector>
#include <fstream>


#define USERNAME_ACCEPTED "331: User name Okay, need password."
#define BAD_SEQUENCE "503: Bad sequence of commands."
#define SUCCESSFUL_LOGIN "230: User logged in, proceed. Logged out if appropriate."
#define INVALID_USER_PASS "430: Invalid username or password"
#define FILE_UNAVAILABLE "550: File unavailable."
#define LIST_TRANSFER_DONE "226: List transfer done."
#define SUCCESSFUL_CHANGE "250: Successful change."
#define SUCCESSFUL_DOWNLOAD "226: Successful Download."
#define SUCCESSFUL_QUIT "221: Successful Quit."
#define NOT_AUTHORIZED "332: Need account for login."
#define SYNTAX_ERROR "501: Syntax error in parameters or arguments."
#define ERROR "500: Error"
#define DOWNLOAD_LIMIT_SIZE "425: Can't open data connection."
#define HELP "214\n- user [name], Its argument is used to specify the user's string. It is used for user authentication.\n\
- pass [password], Its argument is used to specify the user's password string. It is used for user authentication.\n\
- ls It is used to print the list of files/directories in the current working directory.\n\
- pwd, It is used to print the current working path directory.\n\
- mkd [path], Its argument is used to specify the new directory's path. It is usede to create a new directory. If the command is not followed by an argument the new directory will be the main directory.\n\
- dele [flag] [path], Its(flag) flag is used to specify whether a file (-f) or a directory (-d) will be removed. Its argument is used to specify the file/directory's path. It is usede to remove a file or directory.\n\
- cwd [path], Its argument (may have no argument) is used to specify a path. It is used to change the current directory.\n\
- rename [from] [to], Its arguments are used to specify the old and new file's name. It is used to change name of a file.\n\
- retr [name], Its argument is used to specify a file's name to be downloaded. It is used to download a file.\n\
- help, It is used to see how to use commands.\n\
- quit, It is used to quit from the server.\n"



class UserManager{
public:
    UserManager();
    std::string checkUser(std::vector<User> users,std::string username);
    bool login(std::string pass);
    bool quit();
    bool isLoggedIn();
    User getUser();
private:
    User user;
    bool loggedIn, foundUser;
};

#endif