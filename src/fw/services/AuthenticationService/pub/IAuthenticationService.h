#pragma once
#include "AuthenticationServiceTypes.h"
#include <string>

namespace services
{
    namespace AuthenticationService
    {
        class IAuthenticationService
        {
        public:
            virtual std::string isCredValid(services::AuthenticationService::AuthenticationServiceTypes::LoginData) = 0;
            virtual bool createUser(services::AuthenticationService::AuthenticationServiceTypes::SingupData) = 0;
        };
    } // namespace services::AuthenticationService
} // namespace services