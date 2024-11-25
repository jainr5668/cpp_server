#ifndef AUTHENTICATIONSERVICE_H
#define AUTHENTICATIONSERVICE_H
#include "logger.h"
#include "IAuthenticationService.h"
#include "AuthenticationServiceInjections.h"

namespace services
{
    namespace AuthenticationService
    {
        class AuthenticationService : public IAuthenticationService
        {
        public:
            AuthenticationService();
            ~AuthenticationService();
            std::string isCredValid(services::AuthenticationService::AuthenticationServiceTypes::LoginData);
            bool createUser(services::AuthenticationService::AuthenticationServiceTypes::SingupData);
            void initialize() override;
            void *getInterface(ModuleUid uid);
            void setInterface(ModuleUid uid, void *interface);
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID(){return GET_MODULE_UID(services::AuthenticationService::IAuthenticationService);};
        private:
            AuthenticationServiceInjections* injections_;
            Logger logger;
            std::shared_ptr<services::AuthenticationService::AuthenticationService> instance_;
        };
    } // namespace services::AuthenticationService
} // namespace services
#endif // AUTHENTICATIONSERVICE_H
