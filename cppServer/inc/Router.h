#pragma once

#include "IAuthentication.h"
#include "IRouter.h"
#include "logger.h"
#include "ServerTypes.h"

#include <memory>
#include <string>
#include <vector>

using IAuthentication = Server::IAuthentication;
using IAuthorization = Server::IAuthorization;
using IRouter = Server::IRouter;
using Logger = Server::Logger;

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
        std::vector<ServerTypes::Route> routes;
        std::unordered_map<std::string, std::shared_ptr<IRouter>> subRouters;
        static std::shared_ptr<IAuthentication> authenticator_;
        bool isAuthorized(ServerTypes::RouteContext& context);
        std::string routeTypeToString(ServerTypes::RouteType type);
        void setResponse(ServerTypes::RouteContext& context, int statusCode, const std::string& body);
        std::vector<std::string> splitString(std::string str, char delimiter);
        bool validateScopeAndAccessLevel(const ServerTypes::Route& route, ServerTypes::RouteContext& context);
        bool validateAuthorization(std::vector<std::string> accessList, std::unordered_map<std::string, std::string> payload, std::string propertyName);
        std::unique_ptr<IAuthorization> authHandler_;
        Logger logger;
    };
}// namespace Server
