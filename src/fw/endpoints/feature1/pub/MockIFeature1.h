#pragma once
#include "gmock/gmock.h"
#include "IFeature1.h"

class MockIFeature1 : public IFeature1
{
public:
    MockIFeature1();
    ~MockIFeature1();
    MOCK_METHOD2(handler1, void(Request &req, Response *res));
    MOCK_METHOD2(handler1Sub1, void(Request &req, Response *res));
    MOCK_METHOD2(handler1Sub2, void(Request &req, Response *res));
    MOCK_METHOD1(setupHandler1Routes, void(std::shared_ptr<IServer> server));
};