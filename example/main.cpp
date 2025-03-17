#include "Server.h"
#include "IRouter.h"
#include <memory>
#include "Endpoint1.h"

int main(){
    std::shared_ptr<Server::IRouter> router_ = std::make_shared<Example::Endpoint::Endpoint1>();
    Server::IServer* server_ = new Server::Server();
    server_->setRouter(router_);
    server_->start();
    return 0;
}