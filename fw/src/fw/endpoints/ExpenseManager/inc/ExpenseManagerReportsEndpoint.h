#pragma once
#include "ExpenseManagerInjections.h"
#include "IExpenseManagerReportsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerReportsEndpoint : public IExpenseManagerReportsEndpoint
        {
        public:
            ExpenseManagerReportsEndpoint(endpoints::ExpenseManager::ExpenseManagerInjections* &injection);
            ~ExpenseManagerReportsEndpoint();
            void addReport(RouteContext routeContext);
            void connect();
            void deleteReport(RouteContext routeContext);
            void initialize();
            void getReport(RouteContext routeContext);
            void getReports(RouteContext routeContext);
            void *getInstance();
            void *getInterface(ModuleUid uid);
            void setInterface(ModuleUid uid, void *interface);
            void shutdown();
            void updateReport(RouteContext routeContext);
        private:
            endpoints::ExpenseManager::ExpenseManagerInjections* injections_;
            std::vector<Route> getRoutes();
            Logger logger_;
        };
    }
}