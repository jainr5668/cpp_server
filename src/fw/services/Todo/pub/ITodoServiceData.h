#pragma once
#include <string>
#include <vector>
#include "TodoServiceTypes.h"
namespace services
{
    namespace TodoService
    {
        class ITodoServiceData
        {
        public:
            ~ITodoServiceData() = default;
            virtual std::vector<std::vector<std::string>> retriveTodos(std::string query) = 0;
            virtual bool insertTodo(TodoDbData) = 0;
        };
    } // namespace services::AuthenticationServiceData
} // namespace services