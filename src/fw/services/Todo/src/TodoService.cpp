#include "TodoServiceTypes.h"
#include "TodoService.h"

namespace services
{
    namespace TodoService
    {
        TodoService::TodoService(std::unique_ptr<services::TodoService::TodoServiceInjections> injections)
        {
            injections_ = std::move(injections);
        }

        TodoDbData *TodoService::addTodo(TodoPostData todoPostData, std::string userId)
        {
            logger.info("TodoService::addTodo Entry");
            TodoDBData *result1 = nullptr;
            TodoDBData result(todoPostData);
            result.userId = userId;
            if (injections_->todoServiceData->insertTodo(result)){
            result.userId.reset();
            result1 = new TodoDBData(result);
            }
            logger.info("TodoService::addTodo Exit");
            return result1;
        }

        std::vector<TodoDBData> TodoService::getTodos(std::string userId)
        {
            std::vector<TodoDBData> result;
            std::vector<std::vector<std::string>> dataString = injections_->todoServiceData->retriveTodos(userId);
            for (std::vector<std::string> data : dataString)
            {
                TodoDBData data1(data);
                data1.userId.reset();
                result.push_back(TodoDBData(data1));
            }
            return result;
        }
    }
}
