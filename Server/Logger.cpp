
#include "Logger.hpp"

using namespace std;

Logger::Logger(){

}

Logger::Logger(string path)
: path(path) {
}

void Logger::record(string message) {
    fstream file;
    file.open(path, fstream::in | fstream::out | fstream::app);
    
    auto curr = chrono::system_clock::now();
    time_t currTime = chrono::system_clock::to_time_t(curr);
    
    file << "Time: " <<ctime(&currTime);
    file << message << endl;
    file << "--------\n";
    file.close();
}
