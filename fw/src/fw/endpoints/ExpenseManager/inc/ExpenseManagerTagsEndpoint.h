#ifndef EXPENSEMANAGERTAGSENDPOINT_H
#define EXPENSEMANAGERTAGSENDPOINT_H
#include "ExpenseManagerInjections.h"
#include "IExpenseManagerTagsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerTagsEndpoint : public IExpenseManagerTagsEndpoint
        {
        public:
            ExpenseManagerTagsEndpoint(endpoints::ExpenseManager::ExpenseManagerInjections* &injection);
            ~ExpenseManagerTagsEndpoint();
            void addTag(RouteContext routeContext);
            void connect();
            void deleteTag(RouteContext routeContext);
            void initialize();
            void getTag(RouteContext routeContext);
            void getTags(RouteContext routeContext);
            void *getInstance();
            void *getInterface(ModuleUid uid);
            void setInterface(ModuleUid uid, void *interface);
            void shutdown();
            void updateTag(RouteContext routeContext);
        private:
            endpoints::ExpenseManager::ExpenseManagerInjections* injections_;
            std::vector<Route> getRoutes();
            Logger logger_;
        };
    }
}
#endif // EXPENSEMANAGERTAGSENDPOINT_H