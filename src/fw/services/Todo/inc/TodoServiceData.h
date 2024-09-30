#pragma once
#include <string>
#include <vector>
#include "ITodoServiceData.h"
#include "TodoServiceTypes.h"
#include "Data.h"
#include <memory>
#include "logger.h"
namespace services
{
    namespace TodoService
    {
        class TodoServiceData : public services::TodoService::ITodoServiceData
        {
        public:
            TodoServiceData(std::unique_ptr<Data> data);
            std::vector<std::vector<std::string>> retriveTodos(std::string userId) override;
            bool insertTodo(TodoDbData) override;
        private:
            std::unique_ptr<Data> data_{nullptr};
            Logger logger;
        };
    } // namespace services::AuthenticationServiceData
} // namespace services