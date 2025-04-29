#pragma once

#include "IAuthentication.h"
#include "IRouter.h"
#include "ServerTypes.h"

#include <memory>
#include <string>

using IAuthentication = Server::IAuthentication;
using IRouter = Server::IRouter;

namespace Server
{
    class Router : public IRouter
    {
    public:
        Router() = default;
        ~Router() = default;
        void addAuthenticator(std::shared_ptr<IAuthentication> authenticator) override;
        void addRoute(ServerTypes::Route route) override;
        void addSubRouter(std::string path, std::shared_ptr<IRouter> router) override;
        void routeHandler(ServerTypes::RouteContext requestContent) override;

    private:
        std::string routeTypeToString(ServerTypes::RouteType type);
        std::vector<ServerTypes::Route> routes;
        std::unordered_map<std::string, std::shared_ptr<IRouter>> subRouters;
        static std::shared_ptr<IAuthentication> authenticator_;
        void setResponse(ServerTypes::RouteContext& context, int statusCode, const std::string& body);
        bool isAuthorized(ServerTypes::RouteContext& context);
        bool validateScopeAndAccessLevel(const ServerTypes::Route& route, ServerTypes::RouteContext& context);
        bool validateAuthorization(std::vector<std::string> accessList, std::unordered_map<std::string, std::string> payload, std::string propertyName);
    };
}// namespace Server
