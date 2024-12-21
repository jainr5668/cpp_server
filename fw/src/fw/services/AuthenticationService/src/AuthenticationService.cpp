#include "AuthenticationService.h"
#include <stdexcept>

namespace services
{
    namespace AuthenticationService
    {
        AuthenticationService::AuthenticationService()
        {
            logger.info("AuthenticationService::AuthenticationService Constructor Entry");
            logger.info("AuthenticationService::AuthenticationService Constructor Exit");
        }

        void AuthenticationService::connect()
        {
            logger.info("AuthenticationService::connect");
            bool isNull = false;
            assert(injections_->utilityService != nullptr), "Utility Service is not set";
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
            logger.info("AuthenticationService::isCredValid Entry");
            std::string isLoginSuccess;
            std::vector<std::vector<std::string>> users = injections_->authenticationServiceData_->retriveUsers(
                "SELECT * FROM users WHERE username = '" + loginData_.username.value + "' AND password = '" + loginData_.password.value + "'");
            if (users.size() == 1)
            {
                isLoginSuccess = users[0][0];
            }
            else
            {
                logger.info("AuthenticationService::isCredValid Invalid Credentials");
            }
            logger.info("AuthenticationService::isCredValid Exit");
            return isLoginSuccess;
        }

        void AuthenticationService::initialize()
        {
            logger.info("AuthenticationService::initialize Entry");
            injections_ = new AuthenticationServiceInjections();
            injections_->authenticationServiceData_ = std::make_unique<AuthenticationServiceData>(
                std::make_unique<Data>("AuthenticationServiceData.db"));
            logger.info("AuthenticationService::initialize Exit");
        }
        
        void *AuthenticationService::getInterface(ModuleUid uid)
        {
            logger.info("AuthenticationService::getInterface Entry");
            void *interfacePtr = nullptr;
            if (uid == GET_MODULE_UID(IAuthenticationService))
            {
                interfacePtr = this;
            }
            logger.info("AuthenticationService::getInterface Exit");
            return interfacePtr;
        }
        
        void AuthenticationService::shutdown()
        {
            logger.info("AuthenticationService::shutdown Entry");
            logger.info("AuthenticationService::shutdown Exit");
        }

        AuthenticationService::~AuthenticationService()
        {
            logger.info("AuthenticationService::~AuthenticationService Entry");
            logger.info("AuthenticationService::~AuthenticationService Exit");
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
            logger.info("AuthenticationService::setInterface Entry");
            if (uid == GET_MODULE_UID(services::CommonService::IUtilityService))
            {
                injections_->utilityService = std::shared_ptr<services::CommonService::IUtilityService>(
                    static_cast<services::CommonService::IUtilityService *>(interface));
            }
            logger.info("AuthenticationService::setInterface Exit");
        }

        bool AuthenticationService::createUser(services::AuthenticationService::AuthenticationServiceTypes::SingupData singupData_)
        {
            logger.info("AuthenticationService::createUser Entry");
            bool isUserCreated = false;
            std::vector<std::vector<std::string>> users = injections_->authenticationServiceData_->retriveUsers(
                "SELECT * FROM users WHERE username = '" + singupData_.username.value + "'");
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

        bool AuthenticationService::logoutUser(std::string token)
        {
            logger.info("AuthenticationService::logoutUser Entry");
            if(isUserLoggedOut(token))
            {
                logger.info("AuthenticationService::logoutUser User is not logged in");
                return false;
            }
            bool isUserLoggedOut = injections_->authenticationServiceData_->logoutUser(token);
            logger.info("AuthenticationService::logoutUser Exit");
            return isUserLoggedOut;
        }

        bool AuthenticationService::isUserLoggedOut(std::string token)
        {
            logger.info("AuthenticationService::isUserLoggedOut Entry");
            bool isUserLoggedOut = false;
            std::vector<std::vector<std::string>> users = injections_->authenticationServiceData_->retriveUsers(
                "SELECT * FROM logout WHERE token = '" + token + "'");
            if (users.size() > 0)
            {
                isUserLoggedOut = true;
            }
            logger.info("AuthenticationService::isUserLoggedOut Exit");
            return isUserLoggedOut;
        }
    } // namespace services::AuthenticationService
} // namespace services
