#pragma once
#include "IRouter.h"
#include "feature1.h"
#include "AuthenticationEndpoint.h"
#include "TodoEndpoint.h"

class SubRouterMap
{
public:
    std::map<std::string, std::unique_ptr<IRouter>> getRouterMap()
    {
        std::map<std::string, std::unique_ptr<IRouter>> routerMap;
        routerMap["feature1"] = std::make_unique<Feature1>();
        routerMap["auth"] = std::make_unique<endpoints::AuthenticationEndpoint::AuthenticationEndpoint>();
        routerMap["todos"] = std::make_unique<endpoints::TodoEndpoint::TodoEndpoint>();
        return routerMap;
    }
};