#include "TodoServiceTypes.h"
#include "TodoService.h"

namespace services {
    namespace TodoService {
        TodoService::TodoService(std::unique_ptr<services::TodoService::TodoServiceInjections> injections){
            injections_ = std::move(injections);
        }

        bool TodoService::addTodo(TodoPostData, std::string userId) {
            return false;
        }

        std::vector<TodoDBData> TodoService::getTodos(std::string userId) {
            std::vector<TodoDBData> result;
            return result;
        }
    }
}