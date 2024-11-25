#ifndef TODOSERVICEDATA_H
#define TODOSERVICEDATA_H
#include <string>
#include <vector>
#include "ITodoServiceData.h"
#include "TodoServiceTypes.h"
#include "IData.h"
#include <memory>
#include "logger.h"
namespace services
{
    namespace TodoService
    {
        class TodoServiceData : public services::TodoService::ITodoServiceData
        {
        public:
            TodoServiceData(std::shared_ptr<IData> data);
            std::vector<std::vector<std::string>> retriveTodos(std::string userId) override;
            bool insertTodo(TodoDbData) override;
            bool deleteTodo(std::string userId, std::string todoId) override;
            bool updateTodoById(TodoDbData todo) override;
        private:
            std::shared_ptr<IData> data_{nullptr};
            Logger logger;
        };
    } // namespace services::AuthenticationServiceData
} // namespace services
#endif // TODOSERVICEDATA_H