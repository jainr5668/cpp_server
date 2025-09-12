#include "Router.h"
#include <sstream>

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
        auto routeIt = std::find_if(routes.begin(), routes.end(), [&](const ServerTypes::Route &route)
                                    { return route.route == requestContent.requestContext->getRoute(); });

        if (requestContent.responseContext->getBody().empty() && routeIt == routes.end())
        {
            logger.error("Router::routeHandler - Route not found");
            setResponse(requestContent, 404, "Route not found");
        }
        if (requestContent.responseContext->getBody().empty())
        {
            logger.info("Route found: " + routeIt->route);
            const auto &route = *routeIt;

            if (requestContent.responseContext->getBody().empty() && routeTypeToString(route.type) != requestContent.requestContext->getMethod())
            {
                logger.error("Method not allowed");
                setResponse(requestContent, 405, "Method Not Allowed");
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
        else {
            logger.info("Response already set, skipping route handling");
        }
        authHandler_ = nullptr;
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
        logger.info("Router::routeTypeToString - entering");
        switch (type)
        {
        case ServerTypes::RouteType::GET:
            return "GET";
        case ServerTypes::RouteType::POST:
            return "POST";
        case ServerTypes::RouteType::PUT:
            return "PUT";
        case ServerTypes::RouteType::DELETE:
            return "DELETE";
        default:
            return "UNKNOWN";
        }
        logger.info("Router::routeTypeToString - exiting");
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
            throw std::runtime_error("Authenticator not defined");
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

        result = validateAuthorization(accessLevels, payload, "accessLevel");
        if (result)
        {
            result = validateAuthorization(scopes, payload, "scope");
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
                auto propertyValue = payload.at(propertyName);
                for (const auto &accessLevel : accessList)
                {
                    if (propertyValue == accessLevel)
                    {
                        result = true;
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

} // namespace Server
