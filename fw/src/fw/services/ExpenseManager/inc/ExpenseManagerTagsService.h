#ifndef EXPENSEMANAGERTAGSSERVICE_H
#define EXPENSEMANAGERTAGSSERVICE_H
#include "IExpenseManagerTagsService.h"
#include "ExpenseManagerServiceInjections.h"
#include "logger.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class ExpenseManagerTagsService : public IExpenseManagerTagsService
        {
        public:
            ExpenseManagerTagsService(ExpenseManagerServiceInjections* injections);
            void initialize() override;
            void *getInterface(ModuleUid uid) override;
            void setInterface(ModuleUid uid, void *interface) override;
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID() override;
            ~ExpenseManagerTagsService() = default;

        private:
            Logger logger;
            ExpenseManagerServiceInjections *injections_;
        };
    }
}
#endif // EXPENSEMANAGERTAGSSERVICE_H
