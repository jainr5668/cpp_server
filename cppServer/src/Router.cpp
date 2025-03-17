#include "Router.h"

namespace Server{

    void Router::addRoute(ServerTypes::Route route)
    {
        routes.push_back(route);
    }

    void Router::routeHandler(ServerTypes::RouteContext requestContent)
    {
        for(auto route : routes)
        {
            if( route.route == requestContent.requestContext->getRoute() )
            {
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
