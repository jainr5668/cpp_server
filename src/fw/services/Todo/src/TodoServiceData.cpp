#include "TodoServiceData.h"
#include <iostream>

namespace services
{
    namespace TodoService
    {
        TodoServiceData::TodoServiceData(std::shared_ptr<IData> data)
        {
            logger.info("TodoServiceData::TodoServiceData Constructor Entry");
            data_ = data;
            std::vector<std::string> queries = {
                "CREATE TABLE IF NOT EXISTS todos (id TEXT, userId TEXT NOT NULL, title VARCHAR(255) NOT NULL,description TEXT NOT NULL, status VARCHAR(100), dueDate DATETIME, created_at DATETIME NOT NULL, updated_at DATETIME NOT NULL);"
            };
            for (std::string query : queries)
            {
                data_->execute(query);
            }
            logger.info("TodoServiceData::TodoServiceData Constructor Exit");
        }

        std::vector<std::vector<std::string>> TodoServiceData::retriveTodos(std::string userId)
        {
            std::vector<std::vector<std::string>> result;
            std::string query = "SELECT * FROM todos WHERE userId = '" + userId + "';";
            result = data_->execute(query);
            return result;
        }

        bool TodoServiceData::insertTodo(TodoDbData todoDbData)
        {
            logger.info("TodoServiceData::insertTodo Entry");
            todoDbData;
            logger.info(std::to_string(data_->execute(data_->createInsertQuery("todos", todoDbData)).size()));
            logger.info(data_->createInsertQuery("todos", todoDbData));
            logger.info("TodoServiceData::insertTodo Exit");
            return true;
        }
    } // namespace services::AuthenticationServiceData
} // namespace services