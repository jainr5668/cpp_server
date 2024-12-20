#include "TodoServiceTypes.h"
#include "TodoService.h"
#include "Data.h"
#include "TodoServiceData.h"

        std::shared_ptr<services::TodoService::TodoService> services::TodoService::TodoService::instance_ = nullptr;
namespace services
{
    namespace TodoService
    {
        void* TodoService::getInstance(){
            if (instance_ == nullptr)
            {
                instance_ = std::make_shared<services::TodoService::TodoService>();
            }
            return static_cast<void*>(instance_.get());
        }
        TodoService::TodoService()
        {
        }

        TodoService::~TodoService()
        {
            instance_ = nullptr;
            logger.info("TodoService::~TodoService Entry");
            // delete injections_;
            logger.info("TodoService::~TodoService Exit");
        }

        void TodoService::initialize()
        {
            logger.info("TodoService::initialize Entry");
            injections_ = new services::TodoService::TodoServiceInjections();
            injections_->todoServiceData = std::make_unique<services::TodoService::TodoServiceData>(std::make_unique<Data>("TodoData.db"));
            logger.info("TodoService::initialize Exit");
        }

        void * TodoService::getInterface(ModuleUid uid){
            logger.info("TodoService::getInterface Entry");
            void* interfacePtr = nullptr;
            if(uid == GET_MODULE_UID(ITodoService)){
                interfacePtr = this;
            }
            logger.info("TodoService::getInterface Exit");
            return interfacePtr;
        }

        void TodoService::setInterface(ModuleUid uid, void *interface){
            logger.info("TodoService::setInterface Entry");
            if (uid == GET_MODULE_UID(services::CommonService::IUtilityService))
            {
                injections_->utilityService = std::shared_ptr<services::CommonService::IUtilityService>(
                    static_cast<services::CommonService::IUtilityService *>(interface));
            }
            logger.info("TodoService::setInterface Exit");
        }

        void TodoService::connect()
        {
            logger.info("TodoService::connect Entry");
            assert(injections_->utilityService != nullptr), "Utility Service is not set";
            logger.info("TodoService::connect Exit");
        }

        TodoDbData *TodoService::addTodo(TodoPostData todoPostData, std::string userId)
        {
            logger.info("TodoService::addTodo Entry");
            TodoDBData *result1 = nullptr;
            TodoDBData result(todoPostData);
            result.userId = userId;
            if (injections_->todoServiceData->insertTodo(result))
            {
                result.userId.reset();
                result1 = new TodoDBData(result);
            }
            logger.info("TodoService::addTodo Exit");
            return result1;
        }

        std::vector<TodoDBData> TodoService::getTodos(std::string userId)
        {
            logger.info("TodoService::getTodos Entry");
            logger.info("TodoService::getTodos userId: " + userId);
            std::vector<TodoDBData> result;
            std::vector<std::vector<std::string>> dataString = injections_->todoServiceData->retriveTodos(userId);
            for (std::vector<std::string> data : dataString)
            {
                TodoDBData data1(data);
                data1.userId.reset();
                result.push_back(TodoDBData(data1));
            }
            logger.info("TodoService::getTodos size: " + std::to_string(result.size()));
            logger.info("TodoService::getTodos Exit");
            return result;
        }

        TodoDBData *TodoService::getTodoById(std::string userId, std::string todoId)
        {
            logger.info("TodoService::getTodoById Entry");
            logger.info("TodoService::getTodoById userId: " + userId);
            logger.info("TodoService::getTodoById todoId: " + todoId);
            TodoDBData *result = nullptr;
            auto todos = getTodos(userId);
            if (todos.size() > 0)
            {
                for (auto todo : todos)
                {
                    if (todo.id.value() == todoId)
                    {
                        result = new TodoDBData(todo);
                        break;
                    }
                }
            } else {
                logger.info("TodoService::getTodoById No todos found");
            }
            logger.info("TodoService::getTodoById Exit");
            return result;
        }

        std::string TodoService::deleteTodoById(std::string userId, std::string todoId){
            logger.info("TodoService::deleteTodoById Entry");
            logger.info("TodoService::deleteTodoById userId: " + userId);
            logger.info("TodoService::deleteTodoById todoId: " + todoId);
            std::string result = "ERROR";
            if (injections_->todoServiceData->deleteTodo(userId, todoId))
            {
                result = "";
            }
            logger.info("TodoService::deleteTodoById Exit");
            return result;
        }

        TodoDbData* TodoService::updateTodoById(std::string userId, std::string todoId, TodoDbData* todo){
            logger.info("TodoService::updateTodoById Entry");
            logger.info("TodoService::updateTodoById userId: " + userId);
            logger.info("TodoService::updateTodoById todoId: " + todoId);
            TodoDBData* result = nullptr;
            todo->userId = userId;
            todo->updated_at.value = std::chrono::system_clock::now();
            if (injections_->todoServiceData->updateTodoById(*todo))
            {
                todo->userId.reset();
                result =  new TodoDBData(*todo);
            }
            logger.info("TodoService::updateTodoById Exit");
            return result;
        }
        void TodoService::shutdown()
        {
            logger.info("TodoService::shutdown Entry");
            logger.info("TodoService::shutdown Exit");
        }
    }
}
