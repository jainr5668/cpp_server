#pragma once
#include <memory>
#include "IVfsServiceData.h"

namespace services
{
    class VfsServiceInjections
    {
    public:
        virtual ~VfsServiceInjections() = default;
        std::unique_ptr<services::IVfsServiceData> vfsServiceData{nullptr};
    };
} // namespace services