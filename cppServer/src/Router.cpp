#include "Router.h"
#include <sstream>
#include <algorithm>

using IAuthentication = Server::IAuthentication;

std::shared_ptr<IAuthentication> Server::Router::authenticator_ = nullptr;
namespace Server
{

    void Router::addAuthenticator(std::shared_ptr<IAuthentication> authenticator)
    {
        logger.info("Router::addAuthenticator - entering");
        authenticator_ = authenticator;
        logger.info("Router::addAuthenticator - exiting");
    }

    void Router::addRoute(ServerTypes::Route route)
    {
        logger.info("Router::addRoute - entering");
        routes.push_back(route);
        logger.info("Router::addRoute - exiting");
    }

    void Router::routeHandler(ServerTypes::RouteContext requestContent)
    {
        logger.info("Router::routeHandler - entering");
        auto routeParts = getRouteParts(requestContent.requestContext->getRoute());
        size_t depth = requestContent.requestContext->getRouteDepth();
        std::string currentPart = (depth < routeParts.size()) ? routeParts[depth] : "";

        auto subRouter = std::find_if(subRouters.begin(), subRouters.end(), [&](const auto &pair)
                                      { return pair.first == currentPart; });

        if (subRouter != subRouters.end())
        {
            auto router = subRouter->second;
            if (router)
            {
                requestContent.requestContext->setRouteDepth(requestContent.requestContext->getRouteDepth() + 1);
                router->routeHandler(requestContent);
                return;
            }
        }
        std::vector<ServerTypes::Route> matchedRoutes;
        auto requestParts = getRouteParts(requestContent.requestContext->getRoute(), requestContent.requestContext->getRouteDepth());
        for (const auto &route : routes)
        {
            if (matchRoute(getRouteParts(route.route), requestParts))
            {
                matchedRoutes.push_back(route);
            }
        }
        if (matchedRoutes.empty())
        {
            for (const auto &route : routes)
            {
                auto routeParts = getRouteParts(route.route);
                if (routeParts.size() == requestParts.size())
                {
                    bool isMatch = true;
                    std::unordered_map<std::string, std::string> pathParams;
                    for (size_t i = 0; i < routeParts.size(); ++i)
                    {
                        if (routeParts[i] != requestParts[i])
                        {
                            if (!routeParts[i].empty() && routeParts[i][0] == ':')
                            {
                                if (!requestParts[i].empty())
                                {
                                    std::string paramName = routeParts[i].substr(1);
                                    pathParams[paramName] = requestParts[i];
                                }
                                else
                                {
                                    isMatch = false;
                                    break;
                                }
                            }
                            else
                            {
                                isMatch = false;
                                break;
                            }
                        }
                    }
                    if (isMatch)
                    {
                        matchedRoutes.push_back(route);
                        std::unordered_map<std::string, std::string> combinedPathParams = requestContent.requestContext->getPathParams();
                        for (const auto &[key, value] : pathParams)
                        {
                            combinedPathParams[key] = value;
                        }
                        requestContent.requestContext->setPathParams(combinedPathParams);
                    }
                }
            }
        }
        logger.info("routes count: " + std::to_string(routes.size()));
        logger.info("Matched routes count: " + std::to_string(matchedRoutes.size()));
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> routePathParams;

        // Collect path parameters for matched routes (handles cases where matchRoute matched earlier)
        if (!matchedRoutes.empty())
        {
            for(auto &route : matchedRoutes)
            {
                auto routeParts = getRouteParts(route.route);
                if (routeParts.size() == requestParts.size())
                {
                    std::unordered_map<std::string, std::string> pathParams;
                    for (size_t i = 0; i < routeParts.size(); ++i)
                    {
                        if (routeParts[i] != requestParts[i])
                        {
                            if (!routeParts[i].empty() && routeParts[i][0] == ':')
                            {
                                if (!requestParts[i].empty())
                                {
                                    std::string paramName = routeParts[i].substr(1);
                                    pathParams[paramName] = requestParts[i];
                                }
                            }
                        }
                    }
                    routePathParams[route.route] = pathParams;
                }
            }
        }

        if (requestContent.responseContext->getBody().empty() && matchedRoutes.empty())
        {
            logger.error("Route not found");
            setResponse(requestContent, 404, "Route not found");
        }

        if (!matchedRoutes.empty())
        {
            auto &route = matchedRoutes.front();
            ServerTypes::Route *routePtr{nullptr};
            for (auto &r : matchedRoutes)
            {
                if (routeTypeToString(r.type) == requestContent.requestContext->getMethod())
                {
                    routePtr = &r;
                    break;
                }
            }
            if (routePtr)
            {
                route = *routePtr;
            }
            else
            {
                logger.error("Method not allowed");
                setResponse(requestContent, 405, "Method Not Allowed");
            }

            if (requestContent.responseContext->getBody().empty())
            {
                logger.info("Processing route: " + route.route + " with method: " + routeTypeToString(route.type));
                if (authenticator_ == nullptr)
                {
                    logger.error("Authenticator not defined");
                    throw std::runtime_error("Authenticator not defined");
                }
                authHandler_ = authenticator_->getAuthorization("");
                if (route.authorization.enabled)
                {
                    if (requestContent.responseContext->getBody().empty() && !isAuthorized(requestContent))
                    {
                        logger.error("Unauthorized");
                        setResponse(requestContent, 401, "Unauthorized");
                    }

                    if (requestContent.responseContext->getBody().empty() && !validateScopeAndAccessLevel(route, requestContent))
                    {
                        logger.error("Forbidden");
                        setResponse(requestContent, 403, "Forbidden");
                    }
                }
                try
                {
                    if (requestContent.responseContext->getBody().empty())
                    {
                        if (route.handler == nullptr)
                        {
                            logger.error("Handler not defined");
                            throw std::runtime_error("Handler not defined");
                        }
                        requestContent.requestContext->setPathParams(routePathParams[route.route]);
                        requestContent.responseContext->setAuthorizationHandler(std::move(authHandler_));
                        route.handler(requestContent);
                    }
                }
                catch (const std::exception &e)
                {
                    logger.error("Internal Server Error: " + std::string(e.what()));
                    setResponse(requestContent, 500, "Internal Server Error: " + std::string(e.what()));
                }
            }
        }
        // authHandler_ = nullptr;
        logger.info("Router::routeHandler - exiting");
    }

    void Router::addSubRouter(std::string path, std::shared_ptr<IRouter> router)
    {
        logger.info("Router::addSubRouter - entering");
        subRouters[path] = router;
        logger.info("Router::addSubRouter - exiting");
    }

    std::string Router::routeTypeToString(ServerTypes::RouteType type)
    {
        std::string result;
        switch (type)
        {
        case ServerTypes::RouteType::GET:
            result = "GET";
            break;
        case ServerTypes::RouteType::POST:
            result = "POST";
            break;
        case ServerTypes::RouteType::PUT:
            result = "PUT";
            break;
        case ServerTypes::RouteType::DELETE:
            result = "DELETE";
            break;
        default:
            result = "UNKNOWN";
            break;
        }
        return result;
    }

    void Router::setResponse(ServerTypes::RouteContext &context, int statusCode, const std::string &body)
    {
        logger.info("Router::setResponse - entering");
        context.responseContext->setStatusCode(statusCode);
        context.responseContext->setBody(body);
        logger.info("Router::setResponse - exiting");
    }

    bool Router::isAuthorized(ServerTypes::RouteContext &context)
    {
        logger.info("Router::isAuthorized - entering");
        if (!authenticator_)
        {
            logger.error("Authenticator not defined");
            return false;
        }

        const auto &headers = context.requestContext->getHeaders();
        auto authHeaderIt = headers.find("Authorization");
        if (authHeaderIt == headers.end())
        {
            return false;
        }
        std::string authHeader = authHeaderIt->second;
        auto token = splitString(authHeader, ' ');
        if (token.size() != 3 || token[1] != "Bearer")
        {
            logger.error("Invalid Authorization header format");
            return false;
        }
        if (token[2].empty())
        {
            logger.error("Token is empty");
            return false;
        }
        authHandler_ = authenticator_->getAuthorization(token[2]);
        logger.info("Router::isAuthorized - exiting");
        return authHandler_->isAuthenticated();
    }

    bool Router::validateScopeAndAccessLevel(const ServerTypes::Route &route, ServerTypes::RouteContext &context)
    {
        logger.info("Router::validateScopeAndAccessLevel - entering");
        bool result = false;
        if (!authHandler_)
        {
            logger.error("Authenticator not defined");
            throw std::runtime_error("Authenticator not defined");
        }
        const auto &payload = authHandler_->getPayload();
        const auto &accessLevels = route.authorization.accessLevels;
        const auto &scopes = route.authorization.scopes;

        result = validateAuthorization(accessLevels, payload, "accessLevels");
        if (result)
        {
            result = validateAuthorization(scopes, payload, "scopes");
            if (!result)
            {
                logger.error("Router::validateScopeAndAccessLevel - Token does not have required scope");
            }
        }
        else
        {
            logger.error("Router::validateScopeAndAccessLevel - Token does not have required access level");
        }
        logger.info("Router::validateScopeAndAccessLevel - exiting");
        return result;
    }

    bool Router::validateAuthorization(std::vector<std::string> accessList, std::unordered_map<std::string, std::string> payload, std::string propertyName)
    {
        logger.info("Router::validateAuthorization - entering");
        bool result = false;
        if (accessList.empty())
        {
            result = true;
        }
        if (!result)
        {
            if (payload.find(propertyName) == payload.end())
            {
                result = false;
            }
            else if (payload.at(propertyName).empty())
            {
                result = false;
            }
            else
            {
                auto propertyValue = nlohmann::json::parse(payload.at(propertyName));
                for (const auto &accessLevel : accessList)
                {
                    for (const auto &item : propertyValue)
                    {
                        if (item == accessLevel)
                        {
                            result = true;
                            break;
                        }
                    }
                    if (result)
                    {
                        break;
                    }
                }
            }
        }
        logger.info("Router::validateAuthorization - exiting");
        return result;
    }

    std::vector<std::string> Router::splitString(std::string str, char delimiter)
    {
        logger.info("Router::splitString - entering");
        std::vector<std::string> parts;
        std::string part;
        std::istringstream stream(str);
        while (std::getline(stream, part, delimiter))
        {
            parts.push_back(part);
        }
        logger.info("Router::splitString - exiting");
        return parts;
    }

    std::vector<std::string> Router::getRouteParts(const std::string &routePath, int depth)
    {
        std::vector<std::string> parts;
        std::string part;
        std::istringstream stream(routePath);
        bool isFirst = true;
        if (routePath == "/")
        {
            parts = {"/"};
        }
        else
        {
            while (std::getline(stream, part, '/'))
            {
                if (part.empty() && !isFirst)
                {
                    parts.push_back("/");
                }
                else if (!part.empty())
                {
                    parts.push_back(part);
                }
                isFirst = false;
            }
        }
        if (depth > 0 && depth <= parts.size())
        {
            parts = std::vector<std::string>(parts.begin() + depth, parts.end());
        }
        return parts;
    }

    void Router::notImplementedHandler(Server::ServerTypes::RouteContext requestContent)
    {
        requestContent.responseContext->setStatusCode(501);
    }

    void Router::addCustomRoutes(
        ServerTypes::RouteType type,
        const std::string &route,
        std::function<void(ServerTypes::RouteContext)> handler,
        bool authRequired,
        std::vector<std::string> accessLevels,
        std::vector<std::string> scopes)
    {
        ServerTypes::AuthorizationConfiguration config;
        config.enabled = authRequired;
        config.accessLevels = accessLevels;
        config.scopes = scopes;

        ServerTypes::Route newRoute;
        newRoute.type = type;
        newRoute.route = route;
        newRoute.handler = handler;
        newRoute.authorization = config;

        this->addRoute(newRoute);
    }

    bool Router::matchRoute(const std::vector<std::string> &pattern,
                            const std::vector<std::string> &route)
    {

        size_t pi = 0; // pattern index
        size_t ri = 0; // route index

        while (pi < pattern.size() && ri < route.size())
        {
            const std::string &p = pattern[pi];
            const std::string &r = route[ri];

            // Check if it's a wildcard (matches n segments)
            if (p == "*")
            {
                // If this is the last pattern element, it matches everything remaining
                if (pi == pattern.size() - 1)
                {
                    return true;
                }

                // Try to match the remaining pattern at different positions
                // This handles cases like ["api", "*", "end"] matching ["api", "a", "b", "c", "end"]
                for (size_t i = ri; i <= route.size(); ++i)
                {
                    if (matchRoute(std::vector<std::string>(pattern.begin() + pi + 1, pattern.end()),
                                   std::vector<std::string>(route.begin() + i, route.end())))
                    {
                        return true;
                    }
                }
                return false;
            }
            // Check if it's a parameter pattern (starts with :)
            else if (p.size() > 1 && p[0] == ':')
            {
                // Parameter matches any single segment
                pi++;
                ri++;
            }
            // Literal match
            else
            {
                if (p != r)
                {
                    return false;
                }
                pi++;
                ri++;
            }
        }

        // Handle trailing wildcards in pattern
        while (pi < pattern.size() && pattern[pi] == "*")
        {
            pi++;
        }

        // Both should be exhausted for a complete match
        return pi == pattern.size() && ri == route.size();
    }

} // namespace Server