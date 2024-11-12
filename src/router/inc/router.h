#ifndef ROUTER_H
#define ROUTER_H
#include <string>
#include <map>
#include <functional>
#include <memory>
#include <vector>
#include <regex>
#include "logger.h"
#include "response.h"
#include "request.h"
#include "IRouter.h"
#include "RouterType.h"
#include <string>
#include <vector>
#include <sstream>
#include "BaseService.h"

class Router : public IRouter
{
public:
   void initialize() override{};
   void *getInterface(ModuleUid uid){return nullptr;};
   void setInterface(ModuleUid uid, void *interface) {};
   void connect() override {};
   void *getInstance() override{return nullptr;};
   void shutdown() override {};
   ModuleUid getInterfaceUID(){return "12314";};
   void addRoute(Route route);
   void handle_request(Request *req, Response *res);
   void addSubRouter(const std::string &path, std::shared_ptr<IRouter> subrouter_);

private:
   std::vector<Route> routes;
   std::map<std::string, std::shared_ptr<IRouter>> subRoutes;
   Logger logger;
   std::string routeToRegex(const std::string &route);
   std::vector<std::string> extractParamNames(const std::string &route);
   std::string requestMethodToString(RouteMethod method);
};
#endif // ROUTER_H