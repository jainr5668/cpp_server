#pragma once
#include <fstream>
#include <iostream>
#include "registry.h"
#include <nlohmann/json.hpp>
#include "BaseService.h"

class ObjectFactory
{
public:
    bool discoverDependencies()
    {
        logger_.info("ObjectFactory::discoverDependencies Entry");
        std::string dependenciesFile = "/app/src/router/pub/dependencies.json";
        bool result = false;
        std::ifstream inputFile(dependenciesFile);
        if (!inputFile.is_open())
        {
            logger_.error("Could not open the Dependencies file: " + dependenciesFile);
        }
        else
        {
            inputFile >> jsonData;
            inputFile.close();
            result = true;
        }
        logger_.info("ObjectFactory::discoverDependencies Exit");
        return result;
    }
    void generateServiceDependencies()
    {
        logger_.info("ObjectFactory::generateServiceDependencies Entry");
        for (auto it = jsonData["services"].begin(); it != jsonData["services"].end(); ++it)
        {
            getOrCreateServiceInstance(it.key());
        }
        logger_.info("ObjectFactory::generateServiceDependencies Exit");
    }

    /**
     * @brief Get the Service Instance object
     */
    std::shared_ptr<BaseService> getOrCreateServiceInstance(std::string serviceName)
    {
        logger_.info("ObjectFactory::getService Entry");
        auto it = serviceDependencies.find(serviceName);
        std::shared_ptr<BaseService> interfacePtr = nullptr;
        if (it != serviceDependencies.end())
        {
            logger_.info("ObjectFactory::getService Exit");
            interfacePtr = it->second;
        }
        else
        {
            auto serviceCreator = ServiceRegistry::instance().createService(jsonData["services"][serviceName]["namespace"].get<std::string>());
            if (serviceCreator)
            {
                serviceCreator->initialize();
                for (auto &dependency : jsonData["services"][serviceName]["connections"])
                {
                    auto dependencyService = getOrCreateServiceInstance(dependency["from"].get<std::string>());
                    assert(dependencyService.get() != nullptr), "Dependency not found";
                    auto dUid = GET_MODULE_UID_STR(dependency["name"].get<std::string>());
                    assert(dUid != ""), "Dependency not found";
                    auto interface = dependencyService->getInterface(dUid);
                    assert(interface != nullptr), "Interface not found";
                    serviceCreator->setInterface(dUid, interface);
                }
                serviceCreator->connect();
                serviceDependencies[serviceName] = serviceCreator;
                interfacePtr = serviceCreator;
            }
        }
        logger_.info("ObjectFactory::getService Exit");
        return interfacePtr;
    }
    std::map<std::string, std::shared_ptr<BaseService>> getServiceDependencies()
    {
        logger_.info("ObjectFactory::getServiceDependencies Entry");
        logger_.info("ObjectFactory::getServiceDependencies Exit");
        return serviceDependencies;
    }
    std::map<std::string, std::shared_ptr<IRouter>> getEndpointDependencies()
    {
        logger_.info("ObjectFactory::getEndpointDependencies Entry");
        logger_.info("ObjectFactory::getEndpointDependencies Exit");
        return endpointDependencies;
    }
    void generateEndpointDependencies()
    {
        logger_.info("ObjectFactory::generateEndpointDependencies Entry");
        for (auto &endpoint : jsonData["endpoints"])
        {
            auto endpointCreator = ServiceRegistry::instance().createRouter(endpoint["namespace"].get<std::string>());
            if (endpointCreator)
            {
                endpointCreator->initialize();
                for (auto &dependency : endpoint["connections"])
                {
                    auto dependencyService = getOrCreateServiceInstance(dependency["from"].get<std::string>());
                    auto dUid = GET_MODULE_UID_STR(dependency["name"].get<std::string>());
                    endpointCreator->setInterface(dUid, dependencyService->getInterface(dUid));
                }
                endpointCreator->connect();
                endpointDependencies[endpoint["name"]] = endpointCreator;
            }
        }
        logger_.info("ObjectFactory::generateEndpointDependencies Exit");
    }

private:
    nlohmann::json jsonData;
    std::map<std::string, std::shared_ptr<BaseService>> serviceDependencies;
    std::map<std::string, std::shared_ptr<IRouter>> endpointDependencies;
    Logger logger_;
};

class SubRouterMap
{
public:
    SubRouterMap()
    {
        logger_.info("SubRouterMap::SubRouterMap Entry");
        ObjectFactory o;
        if (o.discoverDependencies())
        {
            o.generateServiceDependencies();
            serviceMap_ = o.getServiceDependencies();
            o.generateEndpointDependencies();
            routerMap_ = o.getEndpointDependencies();
        }
        logger_.info("SubRouterMap::SubRouterMap Exit");
    }

    ~SubRouterMap()
    {
        logger_.info("SubRouterMap::~SubRouterMap Shutting down the services and routers");
        for (auto &router : routerMap_)
        {
            router.second->shutdown();
        }
        for (auto &service : serviceMap_)
        {
            service.second->shutdown();
        }
        logger_.info("SubRouterMap::~SubRouterMap Services and routers are shutdown");
    }

    std::map<std::string, std::shared_ptr<IRouter>> getRouterMap()
    {
        return routerMap_;
    }

    std::map<std::string, std::shared_ptr<BaseService>> getServiceMap()
    {
        return serviceMap_;
    }

private:
    std::map<std::string, std::shared_ptr<BaseService>> serviceMap_;
    std::map<std::string, std::shared_ptr<IRouter>> routerMap_;
    Logger logger_;
};