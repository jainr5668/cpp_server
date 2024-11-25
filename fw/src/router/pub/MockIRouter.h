#ifndef MOCKIROUTER_H
#define MOCKIROUTER_H
#include "IRouter.h"
#include "gmock/gmock.h"

class MockIRouter : public IRouter
{
    public:
    MockIRouter();
    ~MockIRouter();
    MOCK_METHOD4(addSubRoute, void(const std::string& parentPath, const std::string& subPath, const std::string& method, HandlerFunc handler));
    MOCK_METHOD3(addRoute, void(const std::string& path, const std::string& method, HandlerFunc handler));
    MOCK_METHOD2(handle_request, void(Request& req, Response* res));
}
#endif // MOCKIROUTER_H