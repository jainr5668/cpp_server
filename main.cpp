#include <iostream>
#include "RequestContent.h"
#include "Server.h"


int main(){
    Server::IServer* server_ = new Server::Server();
    server_->start();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}