#include "AuthenticationService.h"
#include <stdexcept>

namespace services
{
    namespace AuthenticationService
    {
        AuthenticationService::AuthenticationService()
        {
            logger.info("AuthenticationService::AuthenticationService Constructor Entry");

            instance_ = std::shared_ptr<AuthenticationService>(this);
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

        void AuthenticationService::initialize()
        {
            logger.info("AuthenticationService::initialize Entry");
            injections_ = new AuthenticationServiceInjections();
            injections_->authenticationServiceData_ = std::make_unique<AuthenticationServiceData>(std::make_unique<Data>("AuthenticationServiceData.db"));
            logger.info("AuthenticationService::initialize Exit");
        }
        void *AuthenticationService::getInterface(ModuleUid uid)
        {
            logger.info("AuthenticationService::getInterface Entry");
            void *interfacePtr = nullptr;
            if (uid == GET_MODULE_UID(IAuthenticationService))
            {
                interfacePtr = static_cast<IAuthenticationService *>(getInstance());
            }
            logger.info("AuthenticationService::getInterface Exit");
            return nullptr;
        }
        void AuthenticationService::shutdown()
        {
            logger.info("AuthenticationService::shutdown Entry");
            delete injections_;
            logger.info("AuthenticationService::shutdown Exit");
        }
        void *AuthenticationService::getInstance()
        {
            logger.info("AuthenticationService::getInstance Entry");
            if (instance_ == nullptr)
            {
                instance_ = std::make_shared<services::AuthenticationService::AuthenticationService>();
            }
            return static_cast<void *>(instance_.get());
            logger.info("AuthenticationService::getInstance Exit");
        }
        void AuthenticationService::setInterface(ModuleUid uid, void *interface)
        {
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