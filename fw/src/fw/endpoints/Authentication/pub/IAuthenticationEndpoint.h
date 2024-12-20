#ifndef IAUTHENTICATIONENDPOINT_H
#define IAUTHENTICATIONENDPOINT_H
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

DEFINE_MODULE_UID(endpoints::AuthenticationEndpoint::IAuthenticationEndpoint, "1234567890")
#endif // IAUTHENTICATIONENDPOINT_H