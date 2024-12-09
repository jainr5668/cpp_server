#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MockIUtilityService.h>
#include "ExpenseManagerEndpointInjections.h"
#include "ExpenseManagerReportsEndpoint.h"

class ExpenseManagerReportsEndpointTest : public ::testing::Test {
protected:
    virtual void SetUp() override;
    virtual void TearDown() override;
    endpoints::ExpenseManager::ExpenseManagerEndpointInjections* injections_;
    endpoints::ExpenseManager::ExpenseManagerReportsEndpoint* endpoint;
    RouteContext routeContext;
};

void ExpenseManagerReportsEndpointTest::SetUp(){
    injections_ = new endpoints::ExpenseManager::ExpenseManagerEndpointInjections();
    injections_->utilityService = std::make_shared<services::CommonService::MockIUtilityService>();
    endpoint = new endpoints::ExpenseManager::ExpenseManagerReportsEndpoint(injections_);
    routeContext.req = new Request();
    routeContext.res = new Response();
}
void ExpenseManagerReportsEndpointTest::TearDown(){
    delete injections_;
    delete endpoint;
}

TEST_F(ExpenseManagerReportsEndpointTest, WhenAddReportIsCalled_ThenReturn500){
    endpoint->addReport(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerReportsEndpointTest, WhenGetReportsIsCalled_ThenReturn500){
    endpoint->getReports(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerReportsEndpointTest, WhenUpdateReportsIsCalled_ThenReturn500){
    endpoint->updateReport(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerReportsEndpointTest, WhenDeleteReportsIsCalled_ThenReturn500){
    endpoint->deleteReport(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}
