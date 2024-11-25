#ifndef ITODOENDPOINT_H
#define ITODOENDPOINT_H
#include "BaseEndpoint.h"
#include "BaseService.h"

namespace endpoints
{
    namespace TodoEndpoint
    {
        class ITodoEndpoint : public BaseEndpoint
        {
        public:
            ~ITodoEndpoint() = default;
            virtual void getTodo(RouteContext routeContext) = 0;
            virtual void getTodos(RouteContext routeContext) = 0;
            virtual void addTodo(RouteContext routeContext) = 0;
            virtual void updateTodo(RouteContext routeContext) = 0;
            virtual void deleteTodo(RouteContext routeContext) = 0;
        };
    }
} // namespace endpoints::Todo
DEFINE_MODULE_UID(endpoints::TodoEndpoint::ITodoEndpoint, "0x00000011")
#endif // ITODOENDPOINT_H
