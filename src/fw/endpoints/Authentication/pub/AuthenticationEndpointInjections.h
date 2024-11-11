#pragma once
#include <memory>
#include "logger.h"
#include "IAuthenticationService.h"

namespace endpoints
{
    namespace AuthenticationEndpoint
    {
        class AuthenticationEndpointInjections
        {
        public:
            std::shared_ptr<Logger> logger{nullptr};
            std::shared_ptr<services::AuthenticationService::IAuthenticationService> authenticationService;
        };
    } // namespace endpoints::AuthenticationEndpoint
} // namespace endpoints