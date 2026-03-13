#pragma once

#include "IAuthorization.h"
#include "logger.h"

#include <unordered_map>

using Logger = Server::Logger;

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
         * @brief Returns the payload of the token provided
         *
         * @param token std::string
         * @returns std::unordered_map<std::string, std::string> of the data in payload
         */
        std::unordered_map<std::string, std::string> getPayload(std::string token);

        /**
         * @brief Validates the token provided
         *
         * @return bool: true if valid else false
         */
        bool isAuthenticated() override;
        private:
        Logger logger;
        std::unordered_map<std::string, std::string> payload_;
        std::string secret;
        std::string token_;
        static int counter_;
    };
} // namespace Server