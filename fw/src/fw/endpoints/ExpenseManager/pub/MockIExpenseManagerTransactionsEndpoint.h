#ifndef MOCKIEXPENSEMANAGERTRANSACTIONSENDPOINT_H
#define MOCKIEXPENSEMANAGERTRANSACTIONSENDPOINT_H
#include "IExpenseManagerTransactionsEndpoint.h"
#include <gmock/gmock.h>
namespace endpoints{
    namespace ExpenseManager{
        class MockIExpenseManagerTransactionsEndpoint : public IExpenseManagerTransactionsEndpoint{
        public:
        MOCK_METHOD1(addTransaction, void(RouteContext routeContext));
        MOCK_METHOD1(getTransaction, void(RouteContext routeContext));
        MOCK_METHOD1(deleteTransaction, void(RouteContext routeContext));
        MOCK_METHOD1(getTransactions, void(RouteContext routeContext));
        MOCK_METHOD1(updateTransaction, void(RouteContext routeContext));
        };
    }
}
#endif // MOCKIEXPENSEMANAGERTRANSACTIONSENDPOINT_H
