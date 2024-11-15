#pragma once
#include <memory>
#include "logger.h"
#include "IAuthenticationService.h"
#include "IUtilityService.h"

namespace endpoints
{
    namespace AuthenticationEndpoint
    {
        class AuthenticationEndpointInjections
        {
        public:
            std::shared_ptr<Logger> logger{nullptr};
            std::shared_ptr<services::AuthenticationService::IAuthenticationService> authenticationService;
            std::shared_ptr<services::CommonService::IUtilityService> utilityService;
        };
    } // namespace endpoints::AuthenticationEndpoint
} // namespace endpoints