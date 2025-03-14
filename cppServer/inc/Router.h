#pragma once

#include <string>
#include <memory>
#include "ServerTypes.h"
#include "IRouter.h"

using IRouter = Server::IRouter;
namespace Server
{
    class Router : public IRouter
    {
    public:
        Router() = default;
        ~Router() = default;
        void addRoute(ServerTypes::Route route) override;
        void routeHandler(ServerTypes::RouteContext requestContent) override;
        void addSubRouter(std::string path, std::shared_ptr<IRouter> router) override;

    private:
        std::vector<ServerTypes::Route> routes;
        std::unordered_map<std::string, std::shared_ptr<IRouter>> subRouters;
    };
}