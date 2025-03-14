#pragma once
#include <vector>
#include <string>
#include <functional>

namespace Server{
namespace ServerTypes{

    enum class ServerType{
        HTTP,
        HTTPS
    };

    enum class RouteType{
        GET,
        POST,
        PUT,
        DELETE
    };

    
    struct RouteContext{};

    struct AuthorizationConfiguration{
        bool enabled;
        std::vector<std::string> accessLevels;
        std::vector<std::string> scopes;
    };


    struct Route{
        RouteType type;
        const char* route;
        AuthorizationConfiguration authorization;
        std::function<void(void)> handler;
    };
} // namespace ServerTypes
} // namespace Server