#ifndef EXPENSEMANAGERACCOUNTSENDPOINT_H
#define EXPENSEMANAGERACCOUNTSENDPOINT_H
#include "ExpenseManagerEndpointInjections.h"
#include "IExpenseManagerAccountsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerAccountsEndpoint : public IExpenseManagerAccountsEndpoint
        {
        public:
            ExpenseManagerAccountsEndpoint(endpoints::ExpenseManager::ExpenseManagerEndpointInjections* &injection);
            ~ExpenseManagerAccountsEndpoint();
            void addAccount(RouteContext routeContext);
            void connect();
            void deleteAccount(RouteContext routeContext);
            void initialize();
            void getAccount(RouteContext routeContext);
            void getAccounts(RouteContext routeContext);
            void *getInstance();
            void *getInterface(ModuleUid uid);
            void setInterface(ModuleUid uid, void *interface);
            void shutdown();
            void updateAccount(RouteContext routeContext);
        private:
            endpoints::ExpenseManager::ExpenseManagerEndpointInjections* injections_;
            std::vector<Route> getRoutes();
            Logger logger_;
        };
    }
}
#endif // EXPENSEMANAGERACCOUNTSENDPOINT_H
