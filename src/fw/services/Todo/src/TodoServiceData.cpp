#include "TodoServiceData.h"
#include <iostream>
#include "Utils.h"

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

        bool TodoServiceData::deleteTodo(std::string userId, std::string todoId)
        {
            logger.info("TodoServiceData::deleteTodo Entry");
            std::string query = "DELETE FROM todos WHERE userId = '" + userId + "' AND id = '" + todoId + "';";
            data_->execute(query);
            logger.info("TodoServiceData::deleteTodo Exit");
            return true;
        }

        bool TodoServiceData::updateTodoById(TodoDbData todo){
            logger.info("TodoServiceData::updateTodoById Entry");
            std::string query = "UPDATE todos SET title = '" + todo.title.value + "', description = '" + todo.description.value + "', status = '" + todo.status.value + "', dueDate = '" + Utils::timepoint_to_string(todo.dueDate.value) + "', updated_at = '" + Utils::timepoint_to_string(todo.updated_at.value) + "' WHERE id = '" + todo.id.value() + "';";
            data_->execute(query);
            logger.info("TodoServiceData::updateTodoById Exit");
            return true;
        }
    } // namespace services::AuthenticationServiceData
} // namespace services