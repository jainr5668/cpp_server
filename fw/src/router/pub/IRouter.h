#ifndef IROUTER_H
#define IROUTER_H
#include <string>
#include <functional>
#include "response.h"
#include "request.h"
#include "RouterType.h"
#include <memory>
#include "BaseService.h"
class IRouter: public BaseService {
public:
   using HandlerFunc = std::function<void(Request& req, Response* res)>;
   virtual void addRoute(Route route) = 0;
   virtual void handle_request(Request* req, Response* res) = 0;
   virtual void addSubRouter(const std::string& path, std::shared_ptr<IRouter> subrouter_) = 0;
};
#endif // IROUTER_H
