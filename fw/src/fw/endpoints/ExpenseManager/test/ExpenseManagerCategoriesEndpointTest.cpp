#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MockIUtilityService.h>
#include <ExpenseManagerInjections.h>
#include "ExpenseManagerCategoriesEndpoint.h"

class ExpenseManagerCategoriesEndpointTest : public ::testing::Test {
protected:
    virtual void SetUp() override;
    virtual void TearDown() override;
    endpoints::ExpenseManager::ExpenseManagerEndpointInjections* injections_;
    endpoints::ExpenseManager::ExpenseManagerCategoriesEndpoint* endpoint;
    RouteContext routeContext;
};
void ExpenseManagerCategoriesEndpointTest::SetUp(){
    injections_ = new endpoints::ExpenseManager::ExpenseManagerEndpointInjections();
    injections_->utilityService = std::make_shared<services::CommonService::MockIUtilityService>();
    endpoint = new endpoints::ExpenseManager::ExpenseManagerCategoriesEndpoint(injections_);
    routeContext.req = new Request();
    routeContext.res = new Response();
}
void ExpenseManagerCategoriesEndpointTest::TearDown(){
    delete injections_;
    delete endpoint;
}

TEST_F(ExpenseManagerCategoriesEndpointTest, WhenAddCategoryIsCalled_ThenReturn500){
    endpoint->addCategory(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerCategoriesEndpointTest, WhenGetCategoriesIsCalled_ThenReturn500){
    endpoint->getCategories(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerCategoriesEndpointTest, WhenUpdateCategoriesIsCalled_ThenReturn500){
    endpoint->updateCategory(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}

TEST_F(ExpenseManagerCategoriesEndpointTest, WhenDeleteCategoriesIsCalled_ThenReturn500){
    endpoint->deleteCategory(routeContext);
    EXPECT_EQ(routeContext.res->status_code, 500);
    EXPECT_EQ(routeContext.res->body, "Not Implemented");
}
