#ifndef EXPENSEMANAGERSERVICE_H
#define EXPENSEMANAGERSERVICE_H

#include "IExpenseManagerService.h"
#include "ExpenseManagerServiceInjections.h"
#include "logger.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class ExpenseManagerService : public IExpenseManagerService
        {
        public:
            ExpenseManagerService();
            void initialize() override;
            void *getInterface(ModuleUid uid) override;
            void setInterface(ModuleUid uid, void *interface) override;
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID();
            ~ExpenseManagerService() override;
        private:
            ExpenseManagerServiceInjections* injections_;
            Logger logger;
        };
    }
}
#endif // EXPENSEMANAGERSERVICE_H
