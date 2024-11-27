#ifndef COMMONSERVICE_H
#define COMMONSERVICE_H
#include "CommonServiceInjections.h"
#include "ICommonService.h"
#include "logger.h"

namespace services
{
    namespace CommonService
    {
        class CommonService : public ICommonService
        {
            public:
            CommonService();
            ~CommonService();
            void initialize() override;
            void *getInterface(ModuleUid uid) override;
            void setInterface(ModuleUid uid, void *interface) override;
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID() override;
            private:
            Logger logger_;
            services::CommonService::CommonServiceInjections* injections_{nullptr};
            int a;
        };
    }
}
#endif // COMMONSERVICE_H
