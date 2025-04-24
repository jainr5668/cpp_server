#include "Router.h"

using IAuthentication = Server::IAuthentication;

std::shared_ptr<IAuthentication> Server::Router::authenticator_ = nullptr;
namespace Server
{

    void Router::addAuthenticator(std::shared_ptr<IAuthentication> authenticator)
    {
        authenticator_ = authenticator;
    }

    void Router::addRoute(ServerTypes::Route route)
    {
        routes.push_back(route);
    }

    void Router::routeHandler(ServerTypes::RouteContext requestContent)
    {
        auto routeIt = std::find_if(routes.begin(), routes.end(), [&](const ServerTypes::Route &route)
                                    { return route.route == requestContent.requestContext->getRoute(); });

        if (requestContent.responseContext->getBody().empty() && routeIt == routes.end())
        {
            setResponse(requestContent, 404, "Route not found");
        }

        const auto &route = *routeIt;

        if (requestContent.responseContext->getBody().empty() && routeTypeToString(route.type) != requestContent.requestContext->getMethod())
        {
            setResponse(requestContent, 405, "Method Not Allowed");
        }

        if (requestContent.responseContext->getBody().empty() && route.authorization.enabled && !isAuthorized(requestContent))
        {
            setResponse(requestContent, 401, "Unauthorized");
        }

        if (requestContent.responseContext->getBody().empty() && !validateScopeAndAccessLevel(route, requestContent))
        {
            setResponse(requestContent, 403, "Forbidden");
        }

        try
        {
            if (requestContent.responseContext->getBody().empty())
            {
                if (route.handler == nullptr)
                {
                    throw std::runtime_error("Handler not defined");
                }
                route.handler(requestContent);
            }
        }
        catch (const std::exception &e)
        {
            setResponse(requestContent, 500, "Internal Server Error: " + std::string(e.what()));
        }
    }

    void Router::addSubRouter(std::string path, std::shared_ptr<IRouter> router)
    {
        subRouters[path] = router;
    }

    std::string Router::routeTypeToString(ServerTypes::RouteType type)
    {
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
    }
    void Router::setResponse(ServerTypes::RouteContext &context, int statusCode, const std::string &body)
    {
        context.responseContext->setStatusCode(statusCode);
        context.responseContext->setBody(body);
    }

    bool Router::isAuthorized(ServerTypes::RouteContext &context)
    {
        if (!authenticator_)
        {
            throw std::runtime_error("Authenticator not defined");
        }

        const auto &headers = context.requestContext->getHeaders();
        auto authHeaderIt = headers.find("Authorization");
        if (authHeaderIt == headers.end())
        {
            return false;
        }

        authenticator_->setAuthorizationToken(authHeaderIt->second);
        return authenticator_->isAuthenticated();
    }

    bool Router::validateScopeAndAccessLevel(const ServerTypes::Route &route, ServerTypes::RouteContext &context)
    {
        bool result = false;
        const auto &payload = authenticator_->getPayload();
        const auto &accessLevels = route.authorization.accessLevels;
        const auto &scopes = route.authorization.scopes;

        result = validateAuthorization(accessLevels, payload, "accessLevel");
        if (result)
        {
            result = validateAuthorization(scopes, payload, "scope");
        }
        return result;
    }
    bool Router::validateAuthorization(std::vector<std::string> accessList, std::unordered_map<std::string, std::string> payload, std::string propertyName)
    {
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
        return result;
    }

} // namespace Server
