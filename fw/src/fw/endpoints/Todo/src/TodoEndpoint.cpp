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

            // auto todoServiceInjections = std::make_unique<TodoServiceInjections>();
            // todoServiceInjections->todoServiceData = std::make_unique<TodoServiceData>(std::make_unique<Data>("TodoData.db"));
            // todoService_ = std::make_unique<TodoService>(std::move(todoServiceInjections));
            logger.info("TodoEndpoint::TodoEndpoint Exit");
        }

        void TodoEndpoint::initialize()
        {
            logger.info("TodoEndpoint::initialize Entry");
            injections_ = new TodoEndpointInjections();
            for (auto route : getRoutes())
            {
                addRoute(route);
            }
            logger.info("TodoEndpoint::initialize Exit");
        }
        void *TodoEndpoint::getInterface(ModuleUid uid)
        {
            logger.info("TodoEndpoint::getInterface Entry");
            logger.info("TodoEndpoint::getInterface Exit");
            return nullptr;
        }
        void TodoEndpoint::setInterface(ModuleUid uid, void *interface)
        {
            logger.info("TodoEndpoint::setInterface Entry");
            if (uid == GET_MODULE_UID(services::TodoService::ITodoService))
            {
                injections_->todoService = std::shared_ptr<TodoService>(static_cast<TodoService *>(interface));
            }
            logger.info("TodoEndpoint::setInterface Exit");
        }
        void TodoEndpoint::connect()
        {
            logger.info("TodoEndpoint::connect Entry");
            assert(injections_->todoService != nullptr), "Todo Service is not set";
            logger.info("TodoEndpoint::connect Exit");
        }
        void *TodoEndpoint::getInstance()
        {
            logger.info("TodoEndpoint::getInstance Entry");
            logger.info("TodoEndpoint::getInstance Exit");
            return nullptr;
        }
        void TodoEndpoint::shutdown()
        {
            logger.info("TodoEndpoint::shutdown Entry");
            logger.info("TodoEndpoint::shutdown Exit");
        }

        void TodoEndpoint::getTodo(RouteContext routeContext)
        {
            logger.info("TodoEndpoint::getTodo Entry");
            std::string todoId = routeContext.path_params.at("id");
            std::string userId = Utils::getValueFromMap(*(routeContext.req->authorization->isAuthorized()), "userId", "");
            logger.info("TodoEndpoint::getTodo userId: " + userId);
            logger.info("TodoEndpoint::getTodo todoId: " + todoId);
            auto todo = injections_->todoService->getTodoById(userId, todoId);
            if (todo != nullptr)
            {
                routeContext.res->status_code = 200;
                routeContext.res->body = objectToJson(*todo);
            }
            else
            {
                routeContext.res->status_code = 404;
                routeContext.res->body = "Not Found";
            }
            logger.info("TodoEndpoint::getTodo Exit");
        }

        void TodoEndpoint::getTodos(RouteContext routeContext)
        {
            logger.info("TodoEndpoint::getTodos Entry");
            auto todos = injections_->todoService->getTodos(Utils::getValueFromMap(*(routeContext.req->authorization->isAuthorized()), "userId", ""));
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
            auto todoPostData = jsonToObject<services::TodoService::TodoPostData>(routeContext.req->body);
            if (todoPostData.dueDate.value < std::chrono::system_clock::now())
            {
                throw std::invalid_argument("dueDate cannot be in the past");
            }
            auto response = injections_->todoService->addTodo(todoPostData, userId);
            if (response == nullptr)
            {
                routeContext.res->status_code = 500;
                routeContext.res->body = "Internal Server Error";
            }
            else
            {
                routeContext.res->status_code = 201;
                routeContext.res->body = objectToJson(*response);
            }
            logger.info("TodoEndpoint::addTodo Exit");
        }

        void TodoEndpoint::updateTodo(RouteContext routeContext)
        {
            logger.info("TodoEndpoint::updateTodo Entry");
            std::string todoId = routeContext.path_params.at("id");
            std::string userId = Utils::getValueFromMap(*(routeContext.req->authorization->isAuthorized()), "userId", "");
            logger.info("TodoEndpoint::updateTodo userId: " + userId);
            logger.info("TodoEndpoint::updateTodo todoId: " + todoId);
            auto todo = injections_->todoService->getTodoById(userId, todoId);
            if (todo != nullptr)
            {
                auto jsonObject = Utils::string_to_json(routeContext.req->body);
                jsonObject.contains("title") ? todo->title.value = jsonObject["title"].get<std::string>() : todo->title.value;
                jsonObject.contains("description") ? todo->description.value = jsonObject["description"].get<std::string>() : todo->description.value;
                todo->status.value = jsonObject.contains("status") ? jsonObject["status"].get<std::string>() : todo->status.value;
                if (jsonObject.contains("dueDate"))
                {
                    auto dueDate = jsonObject["dueDate"].get<std::string>();
                    if (Utils::string_to_timepoint(dueDate) < std::chrono::system_clock::now())
                    {
                        throw std::invalid_argument("dueDate cannot be in the past");
                    }
                    todo->dueDate.value = Utils::string_to_timepoint(dueDate);
                }
                todo = injections_->todoService->updateTodoById(userId, todoId, todo);
                routeContext.res->status_code = 200;
                routeContext.res->body = objectToJson(*todo);
            }
            else
            {
                routeContext.res->status_code = 404;
                routeContext.res->body = "Not Found";
            }
            logger.info("TodoEndpoint::updateTodo Exit");
        }

        void TodoEndpoint::deleteTodo(RouteContext routeContext)
        {
            logger.info("TodoEndpoint::deleteTodo Entry");
            std::string userId = Utils::getValueFromMap(*(routeContext.req->authorization->isAuthorized()), "userId", "");
            std::string todoId = routeContext.path_params.at("id");
            logger.info("TodoEndpoint::deleteTodo userId: " + userId);
            logger.info("TodoEndpoint::deleteTodo todoId: " + todoId);
            std::string response = injections_->todoService->deleteTodoById(userId, todoId);
            if (response.empty())
            {
                routeContext.res->status_code = 204;
            }
            else
            {
                routeContext.res->status_code = 500;
                routeContext.res->body = "Not Implemented";
            }
            logger.info("TodoEndpoint::deleteTodo Exit");
        }

        std::vector<Route> TodoEndpoint::getRoutes()
        {
            std::vector<Route> routes;
            AuthorizationConfig getTodoConfig, getTodosConfig, addTodoConfig, updateTodoConfig, deleteTodoConfig, preflightConfig;

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

            // PATCH /todos/{id}
            updateTodoConfig.enabled = true;
            updateTodoConfig.accessLevels.push_back("admin");
            updateTodoConfig.scope.push_back("api");
            routes.push_back(Route{"/:id", RouteMethod::PATCH, updateTodoConfig,
                                    std::function<void(RouteContext)>(std::bind(&TodoEndpoint::updateTodo, this, std::placeholders::_1))});

            // DELETE /todos/{id}
            deleteTodoConfig.enabled = true;
            deleteTodoConfig.accessLevels.push_back("admin");
            deleteTodoConfig.scope.push_back("api");
            routes.push_back(Route{"/:id", RouteMethod::DELETE, deleteTodoConfig,
                                    std::function<void(RouteContext)>(std::bind(&TodoEndpoint::deleteTodo, this, std::placeholders::_1))});

            preflightConfig.enabled = false;
            for (auto &route : routes)
            {
                routes.push_back(Route{route.path, RouteMethod::OPTIONS, preflightConfig,
                                    std::function<void(RouteContext)>(std::bind(&BaseEndpoint::handlePreflight, this, std::placeholders::_1))});
            }

            return routes;
        }
    }
} // namespace endpoints::TodoEndpoint