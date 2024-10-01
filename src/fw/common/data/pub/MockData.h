#pragma once
#include <gmock/gmock.h>

#include "IData.h"

class MockData : public IData
{
public:
    MockData() {};
    ~MockData() {};
    MOCK_METHOD0(getDbPath, std::string());
    MOCK_METHOD1(execute, std::vector<std::vector<std::string>>(std::string));
};