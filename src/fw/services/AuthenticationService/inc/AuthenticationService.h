#pragma once
#include "logger.h"
#include <IAuthenticationService.h>
#include "AuthenticationServiceInjections.h"

namespace services
{
    namespace AuthenticationService
    {
        class AuthenticationService : public IAuthenticationService
        {
        public:
            AuthenticationService(std::unique_ptr<AuthenticationServiceInjections> injections);
            std::string isCredValid(services::AuthenticationService::AuthenticationServiceTypes::LoginData);
            bool createUser(services::AuthenticationService::AuthenticationServiceTypes::SingupData);
            
        private:
            void connect();
            std::unique_ptr<AuthenticationServiceInjections> injections_{nullptr};
            Logger logger;
        };
    } // namespace services::AuthenticationService
} // namespace services