#include "server.h"
#include "router.h"
#include "SubRouterMap.h"



int main()
{
   std::unique_ptr<Router> router = std::make_unique<Router>();
   SubRouterMap subRouterMap;
   for (auto &subRouter : subRouterMap.getRouterMap())
      router->addSubRouter(subRouter.first, std::move(subRouter.second));
   std::shared_ptr<Server> server = std::make_shared<Server>(std::move(router));
   server->start();
   return 0;
}
