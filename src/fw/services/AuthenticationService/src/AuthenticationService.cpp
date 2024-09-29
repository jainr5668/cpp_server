#include "AuthenticationService.h"
#include <stdexcept>

namespace services
{
    namespace AuthenticationService
    {
        AuthenticationService::AuthenticationService(std::unique_ptr<AuthenticationServiceInjections> injections): injections_(std::move(injections))
        {
            logger.info("AuthenticationService::AuthenticationService Constructor Entry");
            connect();
            logger.info("AuthenticationService::AuthenticationService Constructor Exit");
        }

        void AuthenticationService::connect()
        {
            logger.info("AuthenticationService::connect");
            bool isNull = false;
            std::string errorMessage;
            if (injections_ == nullptr)
            {
                errorMessage = "AuthenticationServiceInjections is null";
                isNull = true;
            }
            if (injections_->authenticationServiceData_ == nullptr)
            {
                errorMessage = "AuthenticationServiceInjections->IAuthenticationServiceData is null";
                isNull = true;
            }
            if (isNull)
            {
                throw std::runtime_error(errorMessage);
            }
            logger.info("AuthenticationService::connect Exit");
        }

        std::string AuthenticationService::isCredValid(services::AuthenticationService::AuthenticationServiceTypes::LoginData loginData_)
        {
            std::string isLoginSuccess;
            std::vector<std::vector<std::string>> users = injections_->authenticationServiceData_->retriveUsers("SELECT * FROM users WHERE username = '" + loginData_.username.value + "' AND password = '" + loginData_.password.value + "'");
            if (users.size() == 1)
            {
                isLoginSuccess = users[0][0];
            }   
            return isLoginSuccess;            
        }

        bool AuthenticationService::createUser(services::AuthenticationService::AuthenticationServiceTypes::SingupData singupData_)
        {
            logger.info("AuthenticationService::createUser Entry");
            bool isUserCreated = false;
            std::vector<std::vector<std::string>> users = injections_->authenticationServiceData_->retriveUsers("SELECT * FROM users WHERE username = '" + singupData_.username.value + "'");
            if (users.size() == 0)
            {
                uint32_t mobile2 = 0;
                if (singupData_.mobile2.has_value())
                {
                    mobile2 = singupData_.mobile2.value();
                }
                injections_->authenticationServiceData_->insertUser(singupData_);
                isUserCreated = true;
            }
            else
            {
                logger.info("AuthenticationService::createUser User already exists");
            }
            logger.info("AuthenticationService::createUser Exit");
            return isUserCreated;
        }
    } // namespace services::AuthenticationService
} // namespace services