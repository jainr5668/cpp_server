#pragma once
#include "ExpenseManagerInjections.h"
#include "IExpenseManagerTransactionsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerTransactionsEndpoint : public IExpenseManagerTransactionsEndpoint
        {
        public:
            ExpenseManagerTransactionsEndpoint(endpoints::ExpenseManager::ExpenseManagerInjections* &injection);
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
            endpoints::ExpenseManager::ExpenseManagerInjections* injections_;
            std::vector<Route> getRoutes();
            Logger logger_;
        };
    }
}