#ifndef MOCKIEXPENSEMANAGERCATEGORIESENDPOINT_H
#define MOCKIEXPENSEMANAGERCATEGORIESENDPOINT_H
#include "IExpenseManagerCategoriesEndpoint.h"
#include <gmock/gmock.h>
namespace endpoints
{
    namespace ExpenseManager
    {
        class MockIExpenseManagerCategoriesEndpoint : public IExpenseManagerCategoriesEndpoint
        {
        public:
        MOCK_METHOD1(getCategories, void(RouteContext routeContext));
        MOCK_METHOD1(addCategory, void(RouteContext routeContext));
        MOCK_METHOD1(updateCategory, void(RouteContext routeContext));
        MOCK_METHOD1(deleteCategory, void(RouteContext routeContext));
        };
    } // namespace endpoints::ExpenseManager
} // namespace endpoints
#endif // MOCKIEXPENSEMANAGERCATEGORIESENDPOINT_H