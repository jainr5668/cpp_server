#ifndef EXPENSEMANAGERTRANSACTIONSSERVICE_H
#define EXPENSEMANAGERTRANSACTIONSSERVICE_H
#include "IExpenseManagerTransactionsService.h"
#include "ExpenseManagerServiceInjections.h"
#include "logger.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class ExpenseManagerTransactionsService : public IExpenseManagerTransactionsService
        {
        public:
            ExpenseManagerTransactionsService(ExpenseManagerServiceInjections* injections);
            void initialize() override;
            void *getInterface(ModuleUid uid) override;
            void setInterface(ModuleUid uid, void *interface) override;
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID() override;
            ~ExpenseManagerTransactionsService() = default;

        private:
            Logger logger;
            ExpenseManagerServiceInjections *injections_;
        };
    }
}
#endif // EXPENSEMANAGERTRANSACTIONSSERVICE_H
