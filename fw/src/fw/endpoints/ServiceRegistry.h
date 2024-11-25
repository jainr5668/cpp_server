#ifndef SERVICEREGISTRY_H
#define SERVICEREGISTRY_H

#include "BaseService.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <iostream>
#include "IRouter.h"
#include "logger.h"

class ServiceRegistry
{
public:
    using ServiceCreator = std::function<std::shared_ptr<BaseService>()>;
    using RouterCreator = std::function<std::shared_ptr<IRouter>()>;

    static ServiceRegistry &instance()
    {
        static ServiceRegistry registry;
        return registry;
    }

    void registerService(const std::string &name, ServiceCreator creator)
    {
        auto it = serviceCreators_.find(name);
        if (it == serviceCreators_.end())
        {
            serviceCreators_[name] = creator;
        }
    }

    std::shared_ptr<BaseService> createService(const std::string &name)
    {
        std::shared_ptr<BaseService> service;
        auto it = serviceCreators_.find(name);
        if (it != serviceCreators_.end())
        {
            service = it->second();
        }
        else
        {
            std::cerr << "Service not found: " << name << std::endl;
        }
        return service;
    }

    void registerRouter(const std::string &name, RouterCreator creator)
    {
        auto it = routerCreators_.find(name);
        if (it == routerCreators_.end())
        {
            routerCreators_[name] = creator;
        }
    }

    std::shared_ptr<IRouter> createRouter(const std::string &name)
    {
        auto it = routerCreators_.find(name);
        if (it != routerCreators_.end())
        {
            return it->second();
        }
        return nullptr;
    }

private:
    std::map<std::string, ServiceCreator> serviceCreators_;
    std::map<std::string, RouterCreator> routerCreators_;
};

#ifndef UNIQUE_ID
#define UNIQUE_ID_IMPL(line) _unique_id_##line
#define UNIQUE_ID(line) UNIQUE_ID_IMPL(line)
#define UNIQUE_VAR UNIQUE_ID(__LINE__)
#endif

#define REGISTER_SERVICE(name, type)                                                                                                      \
    namespace                                                                                                                             \
    {                                                                                                                                     \
        const bool UNIQUE_VAR = []() {                                                                                                    \
            ServiceRegistry::instance().registerService(name, []() -> std::shared_ptr<BaseService> { return std::make_shared<type>(); }); \
            return true;                                                                                                                  \
        }();                                                                                                                              \
    }

#define REGISTER_ROUTER(name, type)                                                                                                  \
    namespace                                                                                                                        \
    {                                                                                                                                \
        const bool UNIQUE_VAR = []() {                                                                                               \
            ServiceRegistry::instance().registerRouter(name, []() -> std::shared_ptr<IRouter> { return std::make_shared<type>(); }); \
            return true;                                                                                                             \
        }();                                                                                                                         \
    }

#endif // SERVICEREGISTRY_H