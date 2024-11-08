#pragma once
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
            TodoService(std::unique_ptr<services::TodoService::TodoServiceInjections> injections);

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
            std::unique_ptr<services::TodoService::TodoServiceInjections> injections_;
            Logger logger;
        };
    } // namespace services::AuthenticationServiceData
} // namespace services