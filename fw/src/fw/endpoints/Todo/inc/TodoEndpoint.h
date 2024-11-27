#ifndef TODOENDPOINT_H
#define TODOENDPOINT_H
#include "ITodoEndpoint.h"
#include "logger.h"
#include <memory>
#include "BaseService.h"
#include "TodoEndpointInjections.h"

namespace endpoints
{
    namespace TodoEndpoint
    {
        class TodoEndpoint  : public ITodoEndpoint
        {
        public:
            TodoEndpoint();
            void getTodo(RouteContext routeContext);
            void getTodos(RouteContext routeContext);
            void addTodo(RouteContext routeContext);
            void updateTodo(RouteContext routeContext);
            void deleteTodo(RouteContext routeContext);
            void initialize();
            void *getInterface(ModuleUid uid);
            void setInterface(ModuleUid uid, void *interface);
            void connect();
            void *getInstance();
            void shutdown();
            ModuleUid getInterfaceUID(){return GET_MODULE_UID(endpoints::TodoEndpoint::ITodoEndpoint);};

        private:
            Logger logger;
            std::vector<Route> getRoutes();
            TodoEndpointInjections* injections_{nullptr};
        };
    } // namespace TodoEndpoint
} // namespace endpoints
#endif // TODOENDPOINT_H
