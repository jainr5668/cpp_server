#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MockIUtilityService.h>
#include <ExpenseManagerInjections.h>
#include "ExpenseManagerTagsEndpoint.h"

class ExpenseManagerTagsEndpointTest : public ::testing::Test {
protected:
    virtual void SetUp() override;
    virtual void TearDown() override;
    endpoints::ExpenseManager::ExpenseManagerEndpointInjections* injections_;
    endpoints::ExpenseManager::ExpenseManagerTagsEndpoint* endpoint;
    RouteContext routeContext;
};

void ExpenseManagerTagsEndpointTest::SetUp(){
    injections_ = new endpoints::ExpenseManager::ExpenseManagerEndpointInjections();
    injections_->utilityService = std::make_shared<services::CommonService::MockIUtilityService>();
    endpoint = new endpoints::ExpenseManager::ExpenseManagerTagsEndpoint(injections_);
    routeContext.req = new Request();
    routeContext.res = new Response();
}
void ExpenseManagerTagsEndpointTest::TearDown(){
    delete injections_;
    delete endpoint;
}

TEST_F(ExpenseManagerTagsEndpointTest, WhenAddTagIsCalled_ThenReturn500){
    endpoint->addTag(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerTagsEndpointTest, WhenGetTagsIsCalled_ThenReturn500){
    endpoint->getTags(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerTagsEndpointTest, WhenUpdateTagsIsCalled_ThenReturn500){
    endpoint->updateTag(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerTagsEndpointTest, WhenDeleteTagsIsCalled_ThenReturn500){
    endpoint->deleteTag(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}
