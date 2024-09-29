#pragma once
#include <string>
#include <functional>
#include "response.h"
#include "request.h"
#include "RouterType.h"
#include <memory>
class IRouter {
public:
   using HandlerFunc = std::function<void(Request& req, Response* res)>;
   virtual void addRoute(Route route) = 0;
   virtual void handle_request(Request* req, Response* res) = 0;
   virtual void addSubRouter(const std::string& path, std::unique_ptr<IRouter> subrouter_) = 0;
};