#ifndef IEXPENSEMANAGERTRANSACTIONSENDPOINT_H
#define IEXPENSEMANAGERTRANSACTIONSENDPOINT_H
#include "BaseEndpoint.h"

namespace endpoints{
    namespace ExpenseManager{
        class IExpenseManagerTransactionsEndpoint : public BaseEndpoint{
            virtual void addTransaction(RouteContext routeContext) = 0;
            virtual void getTransaction(RouteContext routeContext) = 0;
            virtual void deleteTransaction(RouteContext routeContext) = 0;
            virtual void getTransactions(RouteContext routeContext) = 0;
            virtual void updateTransaction(RouteContext routeContext) = 0;
        };
    }
}
DEFINE_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerTransactionsEndpoint, "852728488")
#endif // IEXPENSEMANAGERTRANSACTIONSENDPOINT_H
