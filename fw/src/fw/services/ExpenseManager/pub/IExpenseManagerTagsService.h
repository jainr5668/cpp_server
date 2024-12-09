#ifndef IEXPENSEMANAGERTAGSSERVICE_H
#define IEXPENSEMANAGERTAGSSERVICE_H
#include "BaseService.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class IExpenseManagerTagsService : public BaseService
        {
        public:
            virtual void initialize() = 0;
            virtual void *getInterface(ModuleUid uid) = 0;
            virtual void setInterface(ModuleUid uid, void *interface) = 0;
            virtual void connect() = 0;
            virtual void *getInstance() = 0;
            virtual void shutdown() = 0;
            virtual ModuleUid getInterfaceUID() = 0;
            virtual ~IExpenseManagerTagsService() = default;
        };
    }
}
DEFINE_MODULE_UID(services::ExpenseManagerService::IExpenseManagerTagsService, "SEMSIEMTS1")
#endif // IEXPENSEMANAGERTAGSSERVICE_H
