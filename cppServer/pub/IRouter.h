#pragma once
#include <string>
#include <memory>
#include "ServerTypes.h"

namespace Server
{
    class IRouter
    {
    public:
        virtual void addRoute(ServerTypes::Route route) = 0;
        virtual void routeHandler(ServerTypes::RouteContext requestContent) = 0;
        virtual void addSubRouter(std::string path, std::shared_ptr<IRouter> router) = 0;
    };
}