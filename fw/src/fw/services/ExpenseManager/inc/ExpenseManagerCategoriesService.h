#ifndef EXPENSEMANAGERCATEGORIESSERVICE_H
#define EXPENSEMANAGERCATEGORIESSERVICE_H
#include "IExpenseManagerCategoriesService.h"
#include "ExpenseManagerServiceInjections.h"
#include "logger.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class ExpenseManagerCategoriesService : public IExpenseManagerCategoriesService
        {
        public:
            ExpenseManagerCategoriesService(ExpenseManagerServiceInjections* injections);
            void initialize() override;
            void *getInterface(ModuleUid uid) override;
            void setInterface(ModuleUid uid, void *interface) override;
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID() override;
            ~ExpenseManagerCategoriesService() = default;

        private:
            Logger logger;
            ExpenseManagerServiceInjections *injections_;
        };
    }
}
#endif // EXPENSEMANAGERCATEGORIESSERVICE_H