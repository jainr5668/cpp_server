#ifndef EXPENSEMANAGERCATEGORIESENDPOINT_H
#define EXPENSEMANAGERCATEGORIESENDPOINT_H
#include "IExpenseManagerCategoriesEndpoint.h"
#include "ExpenseManagerInjections.h"

namespace endpoints{
    namespace ExpenseManager{
        class ExpenseManagerCategoriesEndpoint : public IExpenseManagerCategoriesEndpoint{
        public:
            ExpenseManagerCategoriesEndpoint(endpoints::ExpenseManager::ExpenseManagerInjections* &injection);
            ~ExpenseManagerCategoriesEndpoint();
            void getCategories(RouteContext routeContext);
            void addCategory(RouteContext routeContext);
            void updateCategory(RouteContext routeContext);
            void deleteCategory(RouteContext routeContext);
            void connect();
            void initialize();
            void *getInstance();
            void *getInterface(ModuleUid uid);
            void setInterface(ModuleUid uid, void *interface);
            void shutdown();
        private:
            endpoints::ExpenseManager::ExpenseManagerInjections* injections_;
            std::vector<Route> getRoutes();
            Logger logger_;
        };
    }
}
#endif // EXPENSEMANAGERCATEGORIESENDPOINT_H
