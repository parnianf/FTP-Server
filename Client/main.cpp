#include "Client.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    Client ftpClient = Client();
    ftpClient.readPorts(argv[1]);
    ftpClient.run();
    return 0;
}