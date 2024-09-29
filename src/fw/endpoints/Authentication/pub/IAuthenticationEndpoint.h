#pragma once
#include "BaseEndpoint.h"

namespace endpoints
{
    namespace AuthenticationEndpoint
    {
        class IAuthenticationEndpoint : public BaseEndpoint
        {
        public:
            ~IAuthenticationEndpoint() = default;
            virtual void login(RouteContext routeContext) = 0;
        };
    }
} // namespace endpoints::AuthenticationEndpoint