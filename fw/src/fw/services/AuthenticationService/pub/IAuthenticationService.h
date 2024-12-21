#ifndef IAUTHENTICATIONSERVICE_H
#define IAUTHENTICATIONSERVICE_H
#include "AuthenticationServiceTypes.h"
#include <string>
#include "BaseService.h"

namespace services
{
    namespace AuthenticationService
    {
        class IAuthenticationService : public BaseService
        {
        public:
        ~IAuthenticationService() = default;
            virtual std::string isCredValid(services::AuthenticationService::AuthenticationServiceTypes::LoginData) = 0;
            virtual bool createUser(services::AuthenticationService::AuthenticationServiceTypes::SingupData) = 0;
            virtual bool logoutUser(std::string token) = 0;
            virtual bool isUserLoggedOut(std::string token) = 0;
        };
    } // namespace services::AuthenticationService
} // namespace services
DEFINE_MODULE_UID(services::AuthenticationService::IAuthenticationService, "0x98235f");
#endif // IAUTHENTICATIONSERVICE_H
