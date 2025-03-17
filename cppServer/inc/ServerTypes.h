#pragma once
#include <vector>
#include <string>
#include <functional>
#include "IRequestContent.h"
#include "IResponseContent.h"

using IRequestContent = Server::IRequestContent;
using IResponseContent = Server::IResponseContent;

namespace Server
{
    namespace ServerTypes
    {
        enum class ServerType
        {
            HTTP,
            HTTPS
        };

        enum class RouteType
        {
            GET,
            POST,
            PUT,
            DELETE
        };

        struct RouteContext
        {
            IRequestContent *requestContext;
            IResponseContent *responseContext;
        };

        struct AuthorizationConfiguration
        {
            bool enabled;
            std::vector<std::string> accessLevels;
            std::vector<std::string> scopes;
        };

        struct Route
        {
            RouteType type;
            std::string route;
            AuthorizationConfiguration authorization;
            std::function<void(RouteContext)> handler;
        };
    } // namespace ServerTypes
} // namespace Server
