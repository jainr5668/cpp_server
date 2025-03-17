#pragma once

#include "ServerTypes.h"

#include <string>
#include <memory>

namespace Server
{
    class IRouter
    {
    public:
        virtual void addRoute(ServerTypes::Route route) = 0;
        virtual void addSubRouter(std::string path, std::shared_ptr<IRouter> router) = 0;
        virtual void routeHandler(ServerTypes::RouteContext requestContent) = 0;
    };  // namespace IRouter
} // namespace Server
