#include "TodoEndpoint.h"
#include "AuthorizationTypes.h"
#include "TodoServiceInjections.h"
#include "TodoServiceData.h"
#include "TodoService.h"
#include "TodoServiceTypes.h"
#include "Utils.h"
#include "TodoEndpointTypes.h"
#include <string>
#include <Data.h>

using AuthorizationConfig = common::authorization::AuthorizationConfig;
using TodoServiceData = services::TodoService::TodoServiceData;
using TodoServiceInjections = services::TodoService::TodoServiceInjections;
using TodoService = services::TodoService::TodoService;
using TodosGetResponse = endpoints::TodoEndpoint::TodosGetResponse;
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
            auto todos = todoService_->getTodos(Utils::getValueFromMap(*(routeContext.req->authorization->isAuthorized()), "userId", ""));
            routeContext.res->status_code = 200;
            std::vector<std::string> memberIds;
            std::vector<TodoDBData> members;
            for (auto todo : todos)
            {
                memberIds.push_back(todo.id.value());
                members.push_back(todo);
            }
            TodosGetResponse todosGetResponse(memberIds);
            if (Utils::getValueFromMap(routeContext.req->query_params, "includeMembers", "false") == "true")
            {
                todosGetResponse.members = members;
            }
            routeContext.res->body = objectToJson(todosGetResponse);
            logger.info("TodoEndpoint::getTodos Exit");
        }

        void TodoEndpoint::addTodo(RouteContext routeContext)
        {
            logger.info("TodoEndpoint::addTodo Entry");
            std::string userId = Utils::getValueFromMap(*(routeContext.req->authorization->isAuthorized()), "userId", "");
            if (userId.empty())
            {
                routeContext.res->status_code = 401;
                routeContext.res->body = "Unauthorized";
                return;
            }
            auto todoPostData = jsonToObject<services::TodoService::TodoPostData>(routeContext.req->body);
            if (todoPostData.dueDate.value < std::chrono::system_clock::now())
            {
                std::cout << "dueDate cannot be in the past" << std::endl;
                throw std::invalid_argument("dueDate cannot be in the past");
            }
            auto response = todoService_->addTodo(todoPostData, userId);
            if (response == nullptr)
            {
                logger.info("inside if true");
                routeContext.res->status_code = 500;
                routeContext.res->body = "Internal Server Error";
            }
            else
            {
                logger.info("inside if false");
                routeContext.res->status_code = 201;
                routeContext.res->body = objectToJson(*response);
            }
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