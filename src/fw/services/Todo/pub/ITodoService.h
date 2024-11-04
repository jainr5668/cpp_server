#pragma once
#include <string>
#include <vector>
#include "TodoServiceTypes.h"

using TodoPostData = services::TodoService::TodoPostData;
using TodoDBData = services::TodoService::TodoDbData;
namespace services
{
    namespace TodoService
    {
        class ITodoService
        {
        public:
            ~ITodoService() = default;
            
            virtual TodoDbData* addTodo(TodoPostData, std::string userId) = 0;
            virtual std::vector<TodoDBData> getTodos(std::string userId) = 0;
            virtual TodoDBData* getTodoById(std::string userId, std::string todoId) = 0;
            virtual std::string deleteTodoById(std::string userId, std::string todoId) = 0;
            virtual TodoDbData* updateTodoById(std::string userId, std::string todoId, TodoDbData* todo) = 0;
        };
    } // namespace services::AuthenticationServiceData
} // namespace services