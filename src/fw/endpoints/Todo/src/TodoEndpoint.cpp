#include "TodoEndpoint.h"
#include "AuthorizationTypes.h"
#include "TodoServiceInjections.h"
#include "TodoServiceData.h"
#include "TodoService.h"
#include "TodoServiceTypes.h"

using AuthorizationConfig = common::authorization::AuthorizationConfig;
using TodoServiceData = services::TodoService::TodoServiceData;
using TodoServiceInjections = services::TodoService::TodoServiceInjections;
using TodoService = services::TodoService::TodoService;
namespace endpoints
{
    namespace TodoEndpoint
    {
        TodoEndpoint::TodoEndpoint()
        {
            logger.info("TodoEndpoint::TodoEndpoint Entry");
            for (auto route : getRoutes())
            {
                addRoute(route);
            }
            auto todoServiceInjections = std::make_unique<TodoServiceInjections>();
            todoServiceInjections->todoServiceData = std::make_unique<TodoServiceData>(std::make_unique<Data>("TodoData.db"));
            todoService_ = std::make_unique<TodoService>(std::move(todoServiceInjections));
            logger.info("TodoEndpoint::TodoEndpoint Exit");
        }

        void TodoEndpoint::getTodo(RouteContext routeContext)
        {
            logger.info("TodoEndpoint::getTodo Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger.info("TodoEndpoint::getTodo Exit");
        }

        void TodoEndpoint::getTodos(RouteContext routeContext)
        {
            logger.info("TodoEndpoint::getTodos Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger.info("TodoEndpoint::getTodos Exit");
        }

        void TodoEndpoint::addTodo(RouteContext routeContext)
        {
            logger.info("TodoEndpoint::addTodo Entry");
            todoService_->addTodo(jsonToObject<services::TodoService::TodoPostData>(routeContext.req->body));
            logger.info("TodoEndpoint::addTodo Exit");
        }

        void TodoEndpoint::updateTodo(RouteContext routeContext)
        {
            logger.info("TodoEndpoint::updateTodo Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger.info("TodoEndpoint::updateTodo Exit");
        }

        void TodoEndpoint::deleteTodo(RouteContext routeContext)
        {
            logger.info("TodoEndpoint::deleteTodo Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger.info("TodoEndpoint::deleteTodo Exit");
        }

        std::vector<Route> TodoEndpoint::getRoutes()
        {
            std::vector<Route> routes;
            AuthorizationConfig getTodoConfig, getTodosConfig, addTodoConfig, updateTodoConfig, deleteTodoConfig;

            // GET /todo/{id}
            getTodoConfig.enabled = true;
            getTodoConfig.accessLevels.push_back("admin");
            getTodoConfig.scope.push_back("api");
            routes.push_back(Route{"/:id", RouteMethod::GET, getTodoConfig,
                                   std::function<void(RouteContext)>(std::bind(&TodoEndpoint::getTodo, this, std::placeholders::_1))});

            // GET /todos
            getTodosConfig.enabled = true;
            getTodosConfig.accessLevels.push_back("admin");
            getTodosConfig.scope.push_back("api");
            routes.push_back(Route{"/", RouteMethod::GET, getTodosConfig,
                                   std::function<void(RouteContext)>(std::bind(&TodoEndpoint::getTodos, this, std::placeholders::_1))});

            // POST /todos
            addTodoConfig.enabled = true;
            addTodoConfig.accessLevels.push_back("admin");
            addTodoConfig.scope.push_back("api");
            routes.push_back(Route{"/", RouteMethod::POST, addTodoConfig,
                                   std::function<void(RouteContext)>(std::bind(&TodoEndpoint::addTodo, this, std::placeholders::_1))});

            // PUT /todos/{id}
            updateTodoConfig.enabled = true;
            updateTodoConfig.accessLevels.push_back("admin");
            updateTodoConfig.scope.push_back("api");
            routes.push_back(Route{"/:id", RouteMethod::PUT, updateTodoConfig,
                                   std::function<void(RouteContext)>(std::bind(&TodoEndpoint::updateTodo, this, std::placeholders::_1))});

            // DELETE /todos/{id}
            deleteTodoConfig.enabled = true;
            deleteTodoConfig.accessLevels.push_back("admin");
            deleteTodoConfig.scope.push_back("api");
            routes.push_back(Route{"/:id", RouteMethod::DELETE, deleteTodoConfig,
                                   std::function<void(RouteContext)>(std::bind(&TodoEndpoint::deleteTodo, this, std::placeholders::_1))});
            
            return routes;
        }
    }
} // namespace endpoints::TodoEndpoint