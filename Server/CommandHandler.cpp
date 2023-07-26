#include "CommandHandler.hpp"

#include <utility>
#include <sstream>
using namespace std;

string serverPath;
CommandHandler::CommandHandler(){}

CommandHandler::CommandHandler(JsonParser jsonParser, Logger* logger, int dataFd) : jsonParser(jsonParser), logger(logger), dataFd(dataFd){
    serverPath = execCommand("pwd", {});
    clientDirectory = directory = execCommand("cd", {"../Client && pwd"});
}


Request getRequest(string input){
    string argument, command;
    vector<string> args;
    stringstream ss(input);
    getline(ss, command, ' ');
    while(getline(ss, argument, ' ')){
        args.push_back(argument);
    }
    return Request{command, args};
}

string CommandHandler::run(string input){
    
    Request request = getRequest(input);
    try{
        if (request.command == "user")
            return userHandler(request.args[0]);

        else if (request.command == "pass")
            return passHandler(request.args[0]);

        else if (request.command == "help")
            return helpHandler();

        if(!userManager.isLoggedIn())
            throw string(NOT_AUTHORIZED);
        
        else if (request.command == "pwd")
            return pwdHandler(request.args);

        else if (request.command == "mkd")
            return mkdHandler(request.args);

        else if (request.command == "dele")
            return deleHandler(request.args);

        else if (request.command == "ls")
            return lsHandler();

        else if (request.command ==  "cwd")
            return cwdHandler(request.args);

        else if (request.command ==  "rename")
            return renameHandler(request.args);

        else if (request.command == "retr"){
            retrHandler(request.args);
            return string(SUCCESSFUL_DOWNLOAD);
        }

        else if (request.command == "quit")
            return quitHandler();
        else
            throw string(SYNTAX_ERROR);
    }
    catch(string excep)
    {
        return excep;
    }
}

string CommandHandler::userHandler(string username){
    if(userManager.isLoggedIn())
        throw string(ERROR);
    return userManager.checkUser(jsonParser.getUsers(), username);
}

string CommandHandler::passHandler(string pass){
    if(userManager.login(pass)){
        logger->record("User " + userManager.getUser().getUsername() + " logged in.");
        return string(SUCCESSFUL_LOGIN);
    }
}

string CommandHandler::pwdHandler(vector<string> arguments){
    logger->record("User " + userManager.getUser().getUsername() + " entered command pwd.");
    return "257: " + directory;
}

string CommandHandler::mkdHandler(vector<string> arguments){
    execCommand("mkdir", {directory + "/" + arguments[0]});
    logger->record("User " + userManager.getUser().getUsername() + " created " + arguments[0] + " directory.");
    return "257: " + arguments[0] + " created.";
}

string CommandHandler::deleHandler(vector<string> arguments){
    if (jsonParser.isPrivileged(arguments[1]))
        if(!userManager.getUser().isAdmin())
            throw string(FILE_UNAVAILABLE);
            
    if (arguments[0] == "-f"){
        execCommand("rm", {directory + "/" + arguments[1]});
        logger->record("User " + userManager.getUser().getUsername() + " deleted " + arguments[1] + " file.");
        return "250: " + arguments[1] + " deleted.";
    }
    else if (arguments[0] == "-d"){
        execCommand("rm -r", {directory + "/" + arguments[1]});
        logger->record("User " + userManager.getUser().getUsername() + " deleted " + arguments[1] + " directory.");
        return "250: " + arguments[1] + " deleted.";
    }
    else
        throw string(SYNTAX_ERROR);
}

string CommandHandler::lsHandler(){
    vector<string> arg = {directory};
    string output = execCommand("ls", arg);
    logger->record("User " + userManager.getUser().getUsername() + " entered command ls.");
    return output + "\n226: List transfer done.";
}

string CommandHandler::cwdHandler(vector<string> arguments){
    if(arguments.size() == 0){
        logger->record("User " + userManager.getUser().getUsername() + " entered command cwd and changed working directory to the main directory " + clientDirectory+".");
        directory = clientDirectory;
        return clientDirectory;
    }
    directory = execCommand("chdir", {directory + "/" + arguments[0], " && pwd"});
    logger->record("User " + userManager.getUser().getUsername() + " entered command cwd and changed working directory to " + directory + ".");
    return string(SUCCESSFUL_CHANGE);
}

string CommandHandler::renameHandler(vector<string> arguments){
    if (jsonParser.isPrivileged(arguments[0]))
        if(!userManager.getUser().isAdmin())
            throw string(FILE_UNAVAILABLE);
        
    execCommand("mv", {directory + "/" + arguments[0], directory + "/" + arguments[1]});
	logger->record("User " + userManager.getUser().getUsername() + " changed file name from " + arguments[0] + " to " + arguments[1]);
    return string(SUCCESSFUL_CHANGE);
}

void CommandHandler::retrHandler(vector<string> arguments){
    if (jsonParser.isPrivileged(arguments[0]))
        if(!userManager.getUser().isAdmin())
            throw string(FILE_UNAVAILABLE);
    string path = serverPath + "/" + arguments[0];
    ifstream in_file(path, ios::binary);
    in_file.seekg(0, ios::end);
    double file_size = in_file.tellg();

    if (userManager.getUser().getAvailableSize() < file_size/1000)
        throw string(DOWNLOAD_LIMIT_SIZE);
    userManager.getUser().reduceAvailableSize(file_size/1000);
    int file_fd = open(path.c_str(), O_RDONLY);
    sendfile(dataFd, file_fd, NULL, file_size);
    logger->record("User " + userManager.getUser().getUsername() + " downloaded file " + arguments[0] + ".");
}

string CommandHandler::quitHandler(){
    userManager.quit();
    logger->record("User " + userManager.getUser().getUsername() + " logged out successfully.");
    return string(SUCCESSFUL_QUIT);
}

string CommandHandler::helpHandler(){
    return string(HELP);
}


string CommandHandler::execCommand(const string command, const vector<string> arguments){
    char tmpname [L_tmpnam];
    std::tmpnam ( tmpname );
    string bashCommand = command + " ";
    for(string str : arguments){
        bashCommand += str + " ";
    }
    bashCommand = bashCommand + ">> " + tmpname;
    system(bashCommand.c_str());
    ifstream file(tmpname, std::ios::in | std::ios::binary);
    string result;
    if (file) {
        while (!file.eof()) result.push_back(file.get());
        file.close();
    }
    remove(tmpname);
    result.pop_back();
    result.pop_back();
    return result;
}