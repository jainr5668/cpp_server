#pragma once
#include "BaseService.h"
#include <memory>
#include <string>

namespace services
{
    namespace VfsService
    {
        class IVfsService : public BaseService
        {
        public:
            virtual std::string executeCommand(std::string command) = 0;
        };
    } // namespace VfsService
} // namespace services
DEFINE_MODULE_UID(services::VfsService::IVfsService, 1554949053)