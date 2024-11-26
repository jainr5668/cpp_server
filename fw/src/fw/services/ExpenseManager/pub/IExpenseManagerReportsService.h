#ifndef IEXPENSEMANAGERREPORTSSERVICE_H
#define IEXPENSEMANAGERREPORTSSERVICE_H
#include "BaseService.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class IExpenseManagerReportsService : public BaseService
        {
        public:
            virtual void initialize() = 0;
            virtual void *getInterface(ModuleUid uid) = 0;
            virtual void setInterface(ModuleUid uid, void *interface) = 0;
            virtual void connect() = 0;
            virtual void *getInstance() = 0;
            virtual void shutdown() = 0;
            virtual ModuleUid getInterfaceUID() = 0;
            virtual ~IExpenseManagerReportsService() = default;
        };
    }
}
DEFINE_MODULE_UID(services::ExpenseManagerService::IExpenseManagerReportsService, "SEMSIEMRS")
#endif // IEXPENSEMANAGERREPORTSSERVICE_H