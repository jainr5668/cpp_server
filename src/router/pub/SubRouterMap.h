#pragma once
#include <fstream>
#include <iostream>
#include "registry.h"
#include <nlohmann/json.hpp>



class ObjectFactory
{
public:
    void discoverDependencies()
    {
        logger_.info("ObjectFactory::discoverDependencies Entry");
        std::ifstream inputFile("/home/ronak/cpp_server/src/router/pub/dependencies.json");
        if (!inputFile.is_open())
        {
            std::cerr << "Could not open the Dependencies file: " << std::endl;
            return;
        }
        inputFile >> jsonData;
        inputFile.close();
        logger_.info("ObjectFactory::discoverDependencies Exit");
    }
    void generateServiceDependencies()
    {
        logger_.info("ObjectFactory::generateServiceDependencies Entry");
        std::cout << jsonData["services"].size() << std::endl;
        for (auto &service : jsonData["services"])
        {
            std::cout << "Service Namespace: " << service.dump(4) << std::endl;
            std::cout << "Service Name: " << service["name"] << std::endl;
            auto serviceCreator = ServiceRegistry::instance().createService(service["namespace"]);
            if (serviceCreator)
            {
                std::cout << "Service Creator is not null" << std::endl;
            }
            else {
                std::cout << "Service Creator is null" << std::endl;
            }

            if (serviceCreator)
            {
                serviceCreator->initialize();
                serviceCreator->connect();
                serviceDependencies[service["name"].get<std::string>()] = serviceCreator;
            }
        }
        logger_.info("ObjectFactory::generateServiceDependencies Exit");
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
                    auto dependencyService = serviceDependencies[dependency.get<std::string>()];
                    endpointCreator->setInterface(dependencyService->getInterfaceUID(), dependencyService->getInstance());
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
        o.discoverDependencies();
        o.generateServiceDependencies();
        serviceMap_ = o.getServiceDependencies();
        o.generateEndpointDependencies();
        routerMap_ = o.getEndpointDependencies();
        logger_.info("SubRouterMap::SubRouterMap Exit");
    }

    ~SubRouterMap(){
        logger_.info("SubRouterMap::~SubRouterMap Shutting down the services and routers");
        for(auto &router : routerMap_){
            router.second->shutdown();
        }
        for(auto &service : serviceMap_){
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