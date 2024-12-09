#ifndef MOCKIEXPENSEMANAGERACCOUNTSENDPOINT_H
#define MOCKIEXPENSEMANAGERACCOUNTSENDPOINT_H
#include "IExpenseManagerAccountsEndpoint.h"
#include <gmock/gmock.h>
namespace endpoints
{
    namespace ExpenseManager
    {
        class MockIExpenseManagerAccountsEndpoint : public IExpenseManagerAccountsEndpoint
        {
        public:
        MOCK_METHOD1(addAccount, void(RouteContext routeContext));
        MOCK_METHOD1(getAccount, void(RouteContext routeContext));
        MOCK_METHOD1(deleteAccount, void(RouteContext routeContext));
        MOCK_METHOD1(getAccounts, void(RouteContext routeContext));
        MOCK_METHOD1(updateAccount, void(RouteContext routeContext));
        };
    } // namespace endpoints::ExpenseManager
} // namespace endpoints
#endif // MOCKIEXPENSEMANAGERACCOUNTSENDPOINT_H
