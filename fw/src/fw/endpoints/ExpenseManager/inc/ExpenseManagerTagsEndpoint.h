#ifndef EXPENSEMANAGERTAGSENDPOINT_H
#define EXPENSEMANAGERTAGSENDPOINT_H
#include "ExpenseManagerEndpointInjections.h"
#include "IExpenseManagerTagsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerTagsEndpoint : public IExpenseManagerTagsEndpoint
        {
        public:
            ExpenseManagerTagsEndpoint(endpoints::ExpenseManager::ExpenseManagerEndpointInjections* &injection);
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
            endpoints::ExpenseManager::ExpenseManagerEndpointInjections* injections_;
            std::vector<Route> getRoutes();
            Logger logger_;
        };
    }
}
#endif // EXPENSEMANAGERTAGSENDPOINT_H
