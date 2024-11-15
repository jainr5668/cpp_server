#pragma once
#include "BaseEndpoint.h"

namespace endpoints
{
    class IVfsEndpoint : public BaseEndpoint
    {
    public:
        virtual ~IVfsEndpoint() = default;
    };
} // namespace endpoints