#ifndef MOCKTODOSERVICE_H
#define MOCKTODOSERVICE_H
#include "ITodoService.h"
#include "TodoServiceTypes.h"
#include <gmock/gmock.h>

using TodoPostData = services::TodoService::TodoPostData;
using TodoDBData = services::TodoService::TodoDbData;

namespace services{
    namespace TodoService{
        class MockTodoService : public services::TodoService::ITodoService{
            public:
                MOCK_METHOD2(addTodo, TodoDbData*(TodoPostData, std::string));
                MOCK_METHOD1(getTodos, std::vector<TodoDBData>(std::string));
        };
    }
}
#endif // MOCKTODOSERVICE_H
