#ifndef EXPENSEMANAGERREPORTSSERVICE_H
#define EXPENSEMANAGERREPORTSSERVICE_H
#include "IExpenseManagerReportsService.h"
#include "ExpenseManagerServiceInjections.h"
#include "logger.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class ExpenseManagerReportsService : public IExpenseManagerReportsService
        {
        public:
            ExpenseManagerReportsService(ExpenseManagerServiceInjections* injections);
            void initialize() override;
            void *getInterface(ModuleUid uid) override;
            void setInterface(ModuleUid uid, void *interface) override;
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID() override;
            ~ExpenseManagerReportsService() = default;

        private:
            Logger logger;
            ExpenseManagerServiceInjections *injections_;
        };
    }
}
#endif // EXPENSEMANAGERREPORTSSERVICE_H