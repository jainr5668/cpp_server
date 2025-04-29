#pragma once

#include "IAuthorization.h"
#include <unordered_map>

namespace Server
{
    class Authorization : public IAuthorization
    {
    public:
        Authorization(std::string secret, std::string token);

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
        std::string createToken(const std::unordered_map<std::string, std::string>& payload) override;

        /**
         * @brief Returns the payload of the token stored
         *
         * @returns std::unordered_map<std::string, std::string> of the data in payload
         */
        std::unordered_map<std::string, std::string> getPayload() override;

        /**
         * @brief Validates the token provided
         *
         * @return bool: true if valid else false
         */
        bool isAuthenticated() override;
        private:
        std::string secret;
        std::unordered_map<std::string, std::string> payload_;
        std::string token_;
    };
} // namespace Server