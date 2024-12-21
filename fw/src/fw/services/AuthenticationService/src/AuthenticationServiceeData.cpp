#include "AuthenticationServiceData.h"
#include "AuthenticationServiceTypes.h"
#include "Authorization.h"
#include "Utils.h"

namespace services
{
    namespace AuthenticationService
    {
        AuthenticationServiceData::AuthenticationServiceData(std::unique_ptr<Data> data)
        {
            logger.info("AuthenticationServiceData::AuthenticationServiceData Constructor Entry");
            data_ = std::move(data);
            std::vector<std::string> queries = {
                "CREATE TABLE IF NOT EXISTS users (id TEXT, username TEXT, password TEXT, mobile1 NUMBER, mobile2 NUMBER);",
                "CREATE TABLE IF NOT EXISTS logout(token TEXT, exp NUMBER);"
            };
            for (std::string query : queries)
            {
                data_->execute(query);
            }
            logger.info("AuthenticationServiceData::AuthenticationServiceData Constructor Exit");
        }

        std::vector<std::vector<std::string>> AuthenticationServiceData::retriveUsers(std::string query){
            return data_->execute(query);
        }

        void AuthenticationServiceData::insertUser(services::AuthenticationService::AuthenticationServiceTypes::SingupData signupData){
            logger.info("AuthenticationServiceData::insertUser Entry");
            std::string query = "INSERT INTO users (id, username, password, mobile1, mobile2) VALUES ('" + Utils::get_uuid() + "', '" + \
            signupData.username.value + "', '" + signupData.password.value + "', " + std::to_string(signupData.mobile1.value) + ", " + \
            std::to_string(signupData.mobile2.value()) + ")";
            auto res = data_->execute(query);
            logger.info("AuthenticationServiceData::insertUser Exit");
        }

        bool AuthenticationServiceData::logoutUser(std::string token){
            logger.info("AuthenticationServiceData::logoutUser Entry");
            Authorization authorization;
            authorization.setAuthorizationToken(token);
            std::string exp;
            try{
                auto payloadClaims = authorization.isAuthorized();
                if(!payloadClaims){
                    exp = "0";
                }
                else {
                    exp = Utils::getValueFromMap(*payloadClaims, "exp", "0");
                }
            }
            catch(const std::exception& e){
                logger.error("AuthenticationServiceData::logoutUser " + std::string(e.what()));
                exp = "0";
            }
            std::string query = "INSERT INTO logout (token, exp) VALUES ('" + authorization.getAuthorizationToken() + "', " + exp + ")";
            auto res = data_->execute(query);
            logger.info("AuthenticationServiceData::logoutUser Exit");
            return true;
        }
    } // namespace services::AuthenticationServiceData
} // namespace services
