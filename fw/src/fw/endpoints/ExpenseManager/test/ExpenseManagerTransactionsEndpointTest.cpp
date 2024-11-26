#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MockIUtilityService.h>
#include <ExpenseManagerInjections.h>
#include "ExpenseManagerTransactionsEndpoint.h"

class ExpenseManagerTransactionsEndpoint : public ::testing::Test {
protected:
    virtual void SetUp() override;
    virtual void TearDown() override;
    endpoints::ExpenseManager::ExpenseManagerEndpointInjections* injections_;
    endpoints::ExpenseManager::ExpenseManagerTransactionsEndpoint* endpoint;
    RouteContext routeContext;
};

void ExpenseManagerTransactionsEndpoint::SetUp(){
    injections_ = new endpoints::ExpenseManager::ExpenseManagerEndpointInjections();
    injections_->utilityService = std::make_shared<services::CommonService::MockIUtilityService>();
    endpoint = new endpoints::ExpenseManager::ExpenseManagerTransactionsEndpoint(injections_);
    routeContext.req = new Request();
    routeContext.res = new Response();
}
void ExpenseManagerTransactionsEndpoint::TearDown(){
    delete injections_;
    delete endpoint;
}

TEST_F(ExpenseManagerTransactionsEndpoint, WhenAddTransactionIsCalled_ThenReturn500){
    endpoint->addTransaction(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerTransactionsEndpoint, WhenGetTransactionIsCalled_ThenReturn500){
    endpoint->getTransaction(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerTransactionsEndpoint, WhenGetTransactionsIsCalled_ThenReturn500){
    endpoint->getTransactions(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerTransactionsEndpoint, WhenUpdateTransactionsIsCalled_ThenReturn500){
    endpoint->updateTransaction(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerTransactionsEndpoint, WhenDeleteTransactionsIsCalled_ThenReturn500){
    endpoint->deleteTransaction(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}
