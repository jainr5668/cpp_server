#include "TodoServiceTypes.h"
#include "TodoService.h"

namespace services {
    namespace TodoService {
        TodoService::TodoService(std::unique_ptr<services::TodoService::TodoServiceInjections> injections){
            injections_ = std::move(injections);
        }

        TodoDbData TodoService::addTodo(TodoPostData todoPostData, std::string userId) {
            logger.info("TodoService::addTodo Entry");
            TodoDBData result(todoPostData);
            result.userId = userId;
            injections_->todoServiceData->insertTodo(result);
            result.userId.reset();
            logger.info("TodoService::addTodo Exit");
            return result;
        }

        std::vector<TodoDBData> TodoService::getTodos(std::string userId) {
            std::vector<TodoDBData> result;
            return result;
        }
    }
}