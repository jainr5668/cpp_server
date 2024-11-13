#pragma once
#include <string>
#include <vector>
#include "AuthenticationServiceTypes.h"
namespace services
{
    namespace AuthenticationService
    {
        class IAuthenticationServiceData
        {
        public:
            virtual std::vector<std::vector<std::string>> retriveUsers(std::string query) = 0;
            virtual void insertUser(services::AuthenticationService::AuthenticationServiceTypes::SingupData) = 0;
        };
    } // namespace services::AuthenticationServiceData
} // namespace services