#include "TodoServiceData.h"
#include <iostream>

namespace services
{
    namespace TodoService
    {
        TodoServiceData::TodoServiceData(std::unique_ptr<Data> data)
        {
            logger.info("TodoServiceData::TodoServiceData Constructor Entry");
            data_ = std::move(data);
            std::vector<std::string> queries = {
                "CREATE TABLE IF NOT EXISTS todos (id TEXT, userId TEXT NOT NULL, title VARCHAR(255) NOT NULL, status VARCHAR(100), due_date DATETIME, created_at DATETIME NOT NULL, updated_at DATETIME NOT NULL);"
            };
            for (std::string query : queries)
            {
                data_->execute(query);
            }
            logger.info("TodoServiceData::TodoServiceData Constructor Exit");
        }

        std::vector<std::vector<std::string>> TodoServiceData::retriveTodos(std::string query)
        {
            std::vector<std::vector<std::string>> result;
            return result;
        }

        bool TodoServiceData::insertTodo(TodoDbData todoDbData)
        {
            logger.info("TodoServiceData::insertTodo Entry");
            std::string query = "INSERT INTO todos (id, userId, title, status, due_date, created_at, updated_at) VALUES ('" + Utils::get_uuid() + "', '" + todoDbData.userId.value() + "', '" + todoDbData.title.value + "', '" + todoDbData.status.value + "', '"+ Utils::timepoint_to_string(todoDbData.dueDate.value) + "', '" + Utils::timepoint_to_string(todoDbData.creationDate.value) + "', '" + Utils::timepoint_to_string(todoDbData.creationDate.value) + "');";
            data_->execute(query);
            logger.info("TodoServiceData::insertTodo Exit");
            return true;
        }
    } // namespace services::AuthenticationServiceData
} // namespace services