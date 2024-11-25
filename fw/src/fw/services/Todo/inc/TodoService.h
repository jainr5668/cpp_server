#ifndef TODOSERVICE_H
#define TODOSERVICE_H
#include <string>
#include <vector>
#include "ITodoService.h"
#include "TodoServiceTypes.h"
#include "TodoServiceInjections.h"
#include "logger.h"

using TodoPostData = services::TodoService::TodoPostData;
using TodoDBData = services::TodoService::TodoDbData;
namespace services
{
    namespace TodoService
    {
        class TodoService : public services::TodoService::ITodoService
        {
        public:
            TodoService();
            ~TodoService();

            void initialize() override;
            void *getInterface(ModuleUid uid);
            void setInterface(ModuleUid uid, void *interface);
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID(){return GET_MODULE_UID(services::TodoService::ITodoService);};
            /**
             * @brief Add a new todo for a user
             */
            TodoDbData* addTodo(TodoPostData, std::string userId);

            /**
             * @brief Get all todos for a user
             */
            std::vector<TodoDBData> getTodos(std::string userId);

            /**
             * @brief Get a todo by id
             */
            TodoDBData* getTodoById(std::string userId, std::string todoId);

            /**
             * @brief Delete a todo by id
             */
            std::string deleteTodoById(std::string userId, std::string todoId);

            /**
             * @brief Update a todo by id
             */
            TodoDbData* updateTodoById(std::string userId, std::string todoId, TodoDbData* todo);
        private:
        static std::shared_ptr<services::TodoService::TodoService> instance_;
            services::TodoService::TodoServiceInjections* injections_;
            Logger logger;
        };
    } // namespace services::AuthenticationServiceData
} // namespace services
#endif // TODOSERVICE_H
