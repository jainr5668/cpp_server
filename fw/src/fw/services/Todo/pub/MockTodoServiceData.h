#ifndef MOCKTODOSERVICEDATA_H
#define MOCKTODOSERVICEDATA_H
#include "ITodoServiceData.h"
#include "TodoServiceTypes.h"
#include "Data.h"
#include <memory>
#include <gmock/gmock.h>
class MockTodoServiceData : public services::TodoService::ITodoServiceData {
public:
    MOCK_METHOD1(retriveTodos, std::vector<std::vector<std::string>>(std::string query));
    MOCK_METHOD1(insertTodo, bool(services::TodoService::TodoDbData));
};
#endif // MOCKTODOSERVICEDATA_H