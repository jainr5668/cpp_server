#pragma once
#include "ExpenseManagerInjections.h"
#include "IExpenseManagerTransationsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerTransationsEndpoint : public IExpenseManagerTransationsEndpoint
        {
        public:
            ExpenseManagerTransationsEndpoint(endpoints::ExpenseManager::ExpenseManagerInjections* &injection);
            ~ExpenseManagerTransationsEndpoint();
            void addTransation(RouteContext routeContext);
            void connect();
            void deleteTransation(RouteContext routeContext);
            void initialize();
            void getTransation(RouteContext routeContext);
            void getTransations(RouteContext routeContext);
            void *getInstance();
            void *getInterface(ModuleUid uid);
            void setInterface(ModuleUid uid, void *interface);
            void shutdown();
            void updateTransation(RouteContext routeContext);
        private:
            endpoints::ExpenseManager::ExpenseManagerInjections* injections_;
            std::vector<Route> getRoutes();
            Logger logger_;
        };
    }
}