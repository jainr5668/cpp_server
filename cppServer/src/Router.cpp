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
                std::unique_ptr<Server::IAuthorization> authHandler = nullptr;
                if (route.authorization.enabled)
                {
                    if (!authenticator_) throw std::runtime_error("Authenticator not defined");
                    authHandler = authenticator_->getAuthorization(requestContent.requestContext->getHeaders()["Authorization"]);
                    if(!authHandler->isAuthenticated())
                    {
                        requestContent.responseContext->setStatusCode(401);
                        return;
                    }
                }
                try
                {
                    requestContent.responseContext->setAuthorizationHandler(std::move(authHandler));
                    route.handler(requestContent);
                }
                catch (const std::exception &e)
                {
                    requestContent.responseContext->setStatusCode(500);
                    requestContent.responseContext->setBody("Internal Server Error: " + std::string(e.what()));
                }
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
