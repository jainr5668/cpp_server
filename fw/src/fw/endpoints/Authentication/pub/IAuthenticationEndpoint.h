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
DEFINE_MODULE_UID(endpoints::AuthenticationEndpoint::IAuthenticationEndpoint, std::to_string(1234567890))