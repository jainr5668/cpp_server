#pragma once
#include "IVfsEndpoint.h"
#include "BaseService.h"
#include <memory>
#include "VfsService.h"

namespace endpoints
{
    class VfsEndpoint : public IVfsEndpoint
    {
    public:
        VfsEndpoint(std::shared_ptr<BaseService>);
        virtual ~VfsEndpoint() = default;
        std::vector<Route> getRoutes();
        void postVfs(RouteContext routeContext);
    private:
        std::shared_ptr<services::VfsService::VfsService> vfsService_;
    };
} // namespace endpoints