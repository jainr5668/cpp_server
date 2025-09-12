#include "Authentication.h"
#include "Endpoint1.h"
#include "IRouter.h"
#include "Server.h"
#include <memory>

int main(){

    std::shared_ptr<Server::IAuthentication> authenticator_ = std::make_shared<Server::Authentication>();
    std::shared_ptr<Server::IRouter> router_ = std::make_shared<Example::Endpoint::Endpoint1>();
    router_->addAuthenticator(authenticator_);
    Server::IServer* server_ = new Server::Server();
    server_->setRouter(router_);
    server_->start();
    return 0;
}
