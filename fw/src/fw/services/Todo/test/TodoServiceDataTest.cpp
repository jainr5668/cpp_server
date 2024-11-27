#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MockData.h"
#include "TodoServiceData.h"
#include <memory>

class TodoServiceDataTest : public ::testing::Test
{
public:
    services::TodoService::TodoServiceData *todoServiceData;
    MockData dbData;
    void SetUp() override
    {
        //ON_CALL(*dbData, execute(testing::_)).WillByDefault(testing::Return(std::vector<std::vector<std::string>>()));
        //dbData = std::make_shared<MockData>();
        //todoServiceData = new services::TodoService::TodoServiceData(dbData);
    }

    void TearDown() override
    {
        delete todoServiceData;
    }
};

TEST_F(TodoServiceDataTest, WhenRetriveTodosIsCalledThenReturnData)
{
    // std::vector<std::vector<std::string>> data = {{"1", "John", "25", "STUDENT"}};
    // EXPECT_CALL(*dbData, execute(testing::_)).WillOnce(testing::Return(data));
    // auto result = todoServiceData->retriveTodos("1");
    // ASSERT_EQ(result.size(), 1);
    // EXPECT_EQ(result[0][0], "1");
    // EXPECT_EQ(result[0][1], "John");
    // EXPECT_EQ(result[0][2], "25");
    // EXPECT_EQ(result[0][3], "STUDENT");
}
