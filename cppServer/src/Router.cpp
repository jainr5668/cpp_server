#include "Router.h"

using IAuthentication = Server::IAuthentication;

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
        for (auto route : routes)
        {
            if (route.route == requestContent.requestContext->getRoute())
            {
                if (route.authorization.enabled)
                {
                    if (!authenticator_) throw std::runtime_error("Authenticator not defined");
                    authenticator_->setAuthorizationToken(requestContent.requestContext->getHeaders()["Authorization"]);
                    if(!authenticator_->isAuthenticated())
                    {
                        requestContent.responseContext->setStatusCode(401);
                        return;
                    }
                }
                route.handler(requestContent);
                return;
            }
        }
        requestContent.responseContext->setStatusCode(404);
        requestContent.responseContext->setBody("Route not found");
    }

    void Router::addSubRouter(std::string path, std::shared_ptr<IRouter> router)
    {
        subRouters[path] = router;
    }

} // namespace Server
