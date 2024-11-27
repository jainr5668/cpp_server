#ifndef EXPENSEMANAGERTRANSACTIONSENDPOINT_H
#define EXPENSEMANAGERTRANSACTIONSENDPOINT_H
#include "ExpenseManagerEndpointInjections.h"
#include "IExpenseManagerTransactionsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerTransactionsEndpoint : public endpoints::ExpenseManager::IExpenseManagerTransactionsEndpoint
        {
        public:
            ExpenseManagerTransactionsEndpoint(endpoints::ExpenseManager::ExpenseManagerEndpointInjections* &injection);
            ~ExpenseManagerTransactionsEndpoint();
            void addTransaction(RouteContext routeContext);
            void connect();
            void deleteTransaction(RouteContext routeContext);
            void initialize();
            void getTransaction(RouteContext routeContext);
            void getTransactions(RouteContext routeContext);
            void *getInstance();
            void *getInterface(ModuleUid uid);
            void setInterface(ModuleUid uid, void *interface);
            void shutdown();
            void updateTransaction(RouteContext routeContext);
        private:
            endpoints::ExpenseManager::ExpenseManagerEndpointInjections* injections_;
            std::vector<Route> getRoutes();
            Logger logger_;
        };
    }
}
#endif // EXPENSEMANAGERTRANSACTIONSENDPOINT_H
