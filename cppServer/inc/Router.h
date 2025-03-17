#pragma once

#include "IRouter.h"
#include "ServerTypes.h"

#include <memory>
#include <string>

using IRouter = Server::IRouter;

namespace Server
{
    class Router : public IRouter
    {
    public:
        Router() = default;
        ~Router() = default;
        void addRoute(ServerTypes::Route route) override;
        void addSubRouter(std::string path, std::shared_ptr<IRouter> router) override;
        void routeHandler(ServerTypes::RouteContext requestContent) override;

    private:
        std::vector<ServerTypes::Route> routes;
        std::unordered_map<std::string, std::shared_ptr<IRouter>> subRouters;
    };
}// namespace Server
