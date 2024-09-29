# pragma once

#include "AuthenticationServiceData.h"
#include <memory>

namespace services
{
    namespace AuthenticationService
    {
        class AuthenticationServiceInjections
        {
        public:
            std::unique_ptr<AuthenticationServiceData> authenticationServiceData_{nullptr};
        };
    } // namespace services::AuthenticationServiceData
} // namespace services