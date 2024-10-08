#pragma once
#include "BaseEndpoint.h"

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
