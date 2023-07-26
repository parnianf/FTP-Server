#include "Server.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    Server ftpServer = Server(argv[1]);
    ftpServer.start();
    return 0;
}