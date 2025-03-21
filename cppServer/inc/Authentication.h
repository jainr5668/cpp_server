#pragma once

#include "IAuthentication.h"

#include <string>

using IAuthentication = Server::IAuthentication;

namespace Server
{

    class Authentication : public IAuthentication
    {
    public:
        Authentication() = default;
        ~Authentication() = default;
        /**
         * ======================================================================
         *                  Declaration of virtual functions
         * ======================================================================
         */

        /**
         * @brief Returns the authorization token stored
         *
         * @return std::string token
         */
        std::string getAuthorizationToken();

        /**
         * @brief Returns the payload of the token stored
         *
         * @returns std::unordered_map<std::string, std::string> of the data in payload
         */
        std::unordered_map<std::string, std::string> getPayload();

        /**
         * @brief Validates the token provided
         *
         * @return bool: true if valid else false
         */
        bool isAuthenticated();

        /**
         * @brief Sets the token in object
         *
         * @param authorization_token std::string
         */
        void setAuthorizationToken(const std::string authorization_token);

    private:
        std::string token_;
        std::unordered_map<std::string, std::string> payload_;

        /**
         * @brief Validates the token
         *
         * @return bool - true if valid else false
         */
        bool isTokenValid();
    };

}