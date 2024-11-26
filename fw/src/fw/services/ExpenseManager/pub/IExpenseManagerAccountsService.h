#ifndef IEXPENSEMANAGERACCOUNTSSERVICE_H
#define IEXPENSEMANAGERACCOUNTSSERVICE_H
#include "BaseService.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class IExpenseManagerAccountsService : public BaseService
        {
        public:
            virtual void initialize() = 0;
            virtual void *getInterface(ModuleUid uid) = 0;
            virtual void setInterface(ModuleUid uid, void *interface) = 0;
            virtual void connect() = 0;
            virtual void *getInstance() = 0;
            virtual void shutdown() = 0;
            virtual ModuleUid getInterfaceUID() = 0;
            virtual ~IExpenseManagerAccountsService() = default;
        };
    }
}
DEFINE_MODULE_UID(services::ExpenseManagerService::IExpenseManagerAccountsService, "SEMSIEMAS")
#endif // IEXPENSEMANAGERACCOUNTSSERVICE_H