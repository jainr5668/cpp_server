#pragma once
#include "IRouter.h"
#include "feature1.h"
#include "AuthenticationEndpoint.h"
#include "TodoEndpoint.h"
#include "BaseService.h"

// TodoService
#include "TodoServiceInjections.h"
#include "TodoServiceData.h"
#include "TodoService.h"

class SubRouterMap
{
public:
    SubRouterMap() {
        // TodoEndpoint
        auto todoServiceInjections = std::make_unique<services::TodoService::TodoServiceInjections>();
        todoServiceInjections->todoServiceData = std::make_unique<services::TodoService::TodoServiceData>(std::make_unique<Data>("TodoData.db"));
        auto todoService_ = std::make_shared<services::TodoService::TodoService>(std::move(todoServiceInjections));
        serviceMap_["todos"] = todoService_;
    }

    std::map<std::string, std::unique_ptr<IRouter>> getRouterMap()
    {
        std::map<std::string, std::unique_ptr<IRouter>> routerMap;
        routerMap["feature1"] = std::make_unique<Feature1>();
        routerMap["auth"] = std::make_unique<endpoints::AuthenticationEndpoint::AuthenticationEndpoint>();

        // TodoEndpoint
        routerMap["todos"] = std::make_unique<endpoints::TodoEndpoint::TodoEndpoint>(serviceMap_["todos"]);

        return routerMap;
    }

    std::map<std::string, std::shared_ptr<BaseService>> getServiceMap()
    {
        std::map<std::string, std::shared_ptr<BaseService>> serviceMap_;
    }

private:
    std::map<std::string, std::shared_ptr<BaseService>> serviceMap_;
};