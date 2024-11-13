#pragma once

#include <string>
#include "BaseService.h"

namespace services{
    namespace CommonService{
        class ICommonService : public BaseService
        {
        public:
            virtual void initialize() = 0;
            virtual void *getInterface(ModuleUid uid) = 0;
            virtual void setInterface(ModuleUid uid, void *interface) = 0;
            virtual void connect() = 0;
            virtual void *getInstance() = 0;
            virtual void shutdown() = 0;
            virtual ModuleUid getInterfaceUID() = 0;
            virtual ~ICommonService() = default;
        };
    }
}
DEFINE_MODULE_UID(services::CommonService::ICommonService, "0x00000004")