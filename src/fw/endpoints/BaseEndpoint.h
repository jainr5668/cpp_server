#pragma once
#include "router.h"
#include <string>
#include <nlohmann/json.hpp>
#include "RouterType.h"
#include "AuthorizationTypes.h"
#include "logger.h"

class BaseEndpoint : public Router
{
public:
    Logger logger;
    BaseEndpoint()
    {
        // addRoute(Route{"/", RouteMethod::GET, common::authorization::AuthorizationConfig{}, [](RouteContext routeContext)
        //                {
        //                    routeContext.res->status_code = 404;
        //                    routeContext.res->body = "Please handle this in parent Router";
        //                }});
    }
    ~BaseEndpoint() = default;
    template <typename T>
    T jsonToObject(const std::string &jsonString)
    {
        nlohmann::json j = nlohmann::json::parse(jsonString);
        T obj;
        from_json(j, obj);
        return obj;
    }

    template <typename T>
    std::string objectToJson(const T &obj)
    {
        nlohmann::json j = obj;
        return j.dump();
    }
    void addRoute(Route route) override
    {
        Router::addRoute(route);
    }

    void addSubRouter(std::string path, std::shared_ptr<IRouter> subRouter)
    {
        Router::addSubRouter(path, subRouter);
    }
    void handle_request(Request *req, Response *res) override
    {
        Router::handle_request(req, res);
    }
    virtual void initialize() = 0;
    virtual void *getInterface(ModuleUid uid) = 0;
    virtual void setInterface(ModuleUid uid, void *interface) = 0;
    virtual void connect() = 0;
    virtual void *getInstance() = 0;
    virtual void shutdown() = 0;
};