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
                "CREATE TABLE IF NOT EXISTS users (id TEXT, userId TEXT NOT NULL, title VARCHAR(255) NOT NULL, is_completed BOOLEAN DEFAULT FALSE, due_date DATETIME, created_at DATETIME NOT NULL, updated_at DATETIME NOT NULL);"
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

        bool TodoServiceData::insertTodo(TodoDbData)
        {
        }
    } // namespace services::AuthenticationServiceData
} // namespace services