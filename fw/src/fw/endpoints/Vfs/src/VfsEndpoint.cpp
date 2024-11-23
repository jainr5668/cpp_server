#include "VfsEndpoint.h"
#include "AuthorizationTypes.h"
#include "Utils.h"
#include "VfsServiceTypes.h"

namespace endpoints
{
    VfsEndpoint::VfsEndpoint(std::shared_ptr<BaseService> vfsService)
    {
        logger.info("VfsEndpoint::VfsEndpoint Entry");
            for (auto route : getRoutes())
            {
                addRoute(route);
            }
            vfsService_ = std::dynamic_pointer_cast<services::VfsService::VfsService>(vfsService);
        logger.info("VfsEndpoint::VfsEndpoint Exit");
    }

    void VfsEndpoint::postVfs(RouteContext routeContext)
    {
        logger.info("VfsEndpoint::postVfs Entry");
        auto jsonObject = jsonToObject<services::VfsCommand>(routeContext.req->body);
        logger.info("VfsEndpoint::postVfs jsonObject: " + jsonObject.command.value);
        routeContext.res->status_code = 200;
        routeContext.res->body = vfsService_->executeCommand(jsonObject.command.value);
        logger.info("VfsEndpoint::postVfs Exit");
    }
    std::vector<Route> VfsEndpoint::getRoutes(){
        std::vector<Route> routes;

        // POST /
        common::authorization::AuthorizationConfig postVfsConfig;
        postVfsConfig.enabled = false;
        routes.push_back(Route{"/", RouteMethod::POST, postVfsConfig,
                            std::function<void(RouteContext)>(std::bind(&VfsEndpoint::postVfs, this, std::placeholders::_1))});
        return routes;
    }
} // namespace endpoints