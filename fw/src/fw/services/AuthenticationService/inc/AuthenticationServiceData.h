#ifndef AUTHENTICATIONSERVICEDATA_H
#define AUTHENTICATIONSERVICEDATA_H
#include <IAuthenticationServiceData.h>
#include "Data.h"
#include <memory>
#include <string>
#include <vector>
#include "logger.h"
#include "AuthenticationServiceTypes.h"

namespace services
{
    namespace AuthenticationService
    {
        class AuthenticationServiceData : public IAuthenticationServiceData
        {
        public:
            AuthenticationServiceData(std::unique_ptr<Data> data);
            std::vector<std::vector<std::string>> retriveUsers(std::string query);
            void insertUser(services::AuthenticationService::AuthenticationServiceTypes::SingupData singupData);
            bool logoutUser(std::string token);
        private:
            std::unique_ptr<Data> data_{nullptr};
            Logger logger;
        };
    } // namespace services::AuthenticationServiceData
} // namespace services
#endif // AUTHENTICATIONSERVICEDATA_H
