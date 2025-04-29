#pragma once

#include "IAuthentication.h"

#include <string>

using IAuthentication = Server::IAuthentication;

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
        std::string token_;
        std::unordered_map<std::string, std::string> payload_;
        std::string secret;

        /**
         * @brief Generates a random secret
         *
         * @return std::string - random secret
         */
        std::string generateRandomSecret(size_t length = 32);
        
    };

}