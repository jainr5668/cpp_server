#include "Endpoint1.h"
#include <iostream>

namespace Example{
    namespace Endpoint{
        Endpoint1::Endpoint1(){
            Server::ServerTypes::Route route;
            route.type = Server::ServerTypes::RouteType::GET;
            route.route = "/test";
            route.handler = std::bind(&Endpoint1::function1, this, std::placeholders::_1);
            addRoute(route);
        }
        void Endpoint1::function1(Server::ServerTypes::RouteContext context){
            std::cout << "Hello from route" << std::endl;
            context.responseContext->setStatusCode(200);
            context.responseContext->setBody("Hello from Endpoint route");
        }
    }
}