#ifndef EXPENSEMANAGERACCOUNTSSERVICE_H
#define EXPENSEMANAGERACCOUNTSSERVICE_H
#include "IExpenseManagerAccountsService.h"
#include "ExpenseManagerServiceInjections.h"
#include "logger.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class ExpenseManagerAccountsService : public IExpenseManagerAccountsService
        {
        public:
            ExpenseManagerAccountsService(ExpenseManagerServiceInjections* injections);
            void initialize() override;
            void *getInterface(ModuleUid uid) override;
            void setInterface(ModuleUid uid, void *interface) override;
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID() override;
            ~ExpenseManagerAccountsService() = default;

        private:
            Logger logger;
            ExpenseManagerServiceInjections *injections_;
        };
    }
}
#endif // EXPENSEMANAGERACCOUNTSSERVICE_H
