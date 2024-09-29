#pragma once
#include "gmock/gmock.h"
#include "IServer.h"

class MockIServer : public IServer
{
public:
    MOCK_METHOD4(addSubRoute, void(const std::string &parentPath, const std::string &subPath, const std::string &method, IRouter::HandlerFunc handler));
    MOCK_METHOD3(addHandler, void(const std::string &path, const std::string &method, IRouter::HandlerFunc handler));
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
};