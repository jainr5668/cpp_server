#include <iostream>
#include "RequestContent.h"
#include "Server.h"
#include "Router.h"
#include <memory>
void addRoutes(std::shared_ptr<Server::Router> router_){
    Server::ServerTypes::Route route;
    route.type = Server::ServerTypes::RouteType::GET;
    route.route = "/test";
    route.handler = [](Server::ServerTypes::RouteContext context){
        std::cout << "Hello from route" << std::endl;
        context.responseContext->setStatusCode(200);
        context.responseContext->setBody("Hello from route");
    };
    router_->addRoute(route);
    route = Server::ServerTypes::Route();
    route.type = Server::ServerTypes::RouteType::GET;
    route.route = "/";
    route.handler = [](Server::ServerTypes::RouteContext context){
        std::cout << "Hello from home route" << std::endl;
        context.responseContext->setStatusCode(200);
        context.responseContext->setBody("Hello from home route");
    };
    router_->addRoute(route);
    route = Server::ServerTypes::Route();
    route.type = Server::ServerTypes::RouteType::GET;
    route.route = "/error";
    route.handler = [](Server::ServerTypes::RouteContext context){
        std::cout << "Hello from home route" << std::endl;
        context.responseContext->setStatusCode(500);
        context.responseContext->setBody("Error from home route");
    };
    router_->addRoute(route);
}

int main(){
    std::shared_ptr<Server::Router> router_ = std::make_shared<Server::Router>();
    addRoutes(router_);
    Server::IServer* server_ = new Server::Server();
    server_->setRouter(router_);
    server_->start();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}