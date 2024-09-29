#pragma once
#include "ITodoEndpoint.h"
#include "logger.h"
#include "TodoService.h"
#include <memory>

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
        private:
            Logger logger;
            std::vector<Route> getRoutes();
            std::unique_ptr<services::TodoService::TodoService> todoService_;
        };
    } // namespace TodoEndpoint
} // namespace endpoints