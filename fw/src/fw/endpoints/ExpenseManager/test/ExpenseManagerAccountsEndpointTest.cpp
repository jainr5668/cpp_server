#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MockIUtilityService.h>
#include "ExpenseManagerEndpointInjections.h"
#include <ExpenseManagerAccountsEndpoint.h>

class ExpenseManagerAccountsEndpointTest : public ::testing::Test {
protected:
    virtual void SetUp() override;
    virtual void TearDown() override;
    endpoints::ExpenseManager::ExpenseManagerEndpointInjections* injections_;
    endpoints::ExpenseManager::ExpenseManagerAccountsEndpoint* endpoint;
    RouteContext routeContext;
};

void ExpenseManagerAccountsEndpointTest::SetUp(){
    injections_ = new endpoints::ExpenseManager::ExpenseManagerEndpointInjections();
    injections_->utilityService = std::make_shared<services::CommonService::MockIUtilityService>();
    endpoint = new endpoints::ExpenseManager::ExpenseManagerAccountsEndpoint(injections_);
    routeContext.req = new Request();
    routeContext.res = new Response();
}
void ExpenseManagerAccountsEndpointTest::TearDown(){
    delete injections_;
    delete endpoint;
}

TEST_F(ExpenseManagerAccountsEndpointTest, WhenAddAccountIsCalled_ThenReturn500){
    endpoint->addAccount(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerAccountsEndpointTest, WhenGetAccountIsCalled_ThenReturn500){
    endpoint->getAccount(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerAccountsEndpointTest, WhenGetAccountsIsCalled_ThenReturn500){
    endpoint->getAccounts(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerAccountsEndpointTest, WhenUpdateAccountsIsCalled_ThenReturn500){
    endpoint->updateAccount(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerAccountsEndpointTest, WhenDeleteAccountsIsCalled_ThenReturn500){
    endpoint->deleteAccount(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}
