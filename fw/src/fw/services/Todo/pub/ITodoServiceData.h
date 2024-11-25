#ifndef ITODOSERVICEDATA_H
#define ITODOSERVICEDATA_H
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
            virtual std::vector<std::vector<std::string>> retriveTodos(std::string) = 0;
            virtual bool insertTodo(TodoDbData) = 0;
            virtual bool deleteTodo(std::string, std::string) = 0;
            virtual bool updateTodoById(TodoDbData) = 0;
        };
    } // namespace services::AuthenticationServiceData
} // namespace services
#endif // ITODOSERVICEDATA_H
