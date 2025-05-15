#pragma once

#include "IAuthentication.h"

#include <string>
#include "logger.h"

using IAuthentication = Server::IAuthentication;
using Logger = Server::Logger;

namespace Server
{

    class Authentication : public IAuthentication
    {
    public:
        Authentication();
        ~Authentication() = default;
        /**
         * ======================================================================
         *                  Declaration of virtual functions
         * ======================================================================
         */

        /**
         * @brief Returns the authorization token stored
         *
         * @return std::unique_ptr<IAuthorization> token
         */
        std::unique_ptr<IAuthorization> getAuthorization(std::string token);

        /**
         * @brief Returns the payload of the token stored
         *
         * @returns std::unordered_map<std::string, std::string> of the data in payload
         */
        std::unordered_map<std::string, std::string> getPayload();


        /**
         * @brief Sets the token in object
         *
         * @param authorization_token std::string
         */
        void setAuthorizationToken(const std::string authorization_token);
    private:
        Logger logger;
        std::unordered_map<std::string, std::string> payload_;
        std::string secret;
        std::string token_;

        /**
         * @brief Generates a random secret
         *
         * @return std::string - random secret
         */
        std::string generateRandomSecret(size_t length = 32);
        
    };

}