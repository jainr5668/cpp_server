#pragma once

#include <string>
#include <unordered_map>

namespace Server
{
    class IAuthorization
    {
        public:
        virtual std::string createToken(const std::unordered_map<std::string, std::string>& payload) = 0;
        virtual std::unordered_map<std::string, std::string> getPayload() = 0;
        virtual bool isAuthenticated() = 0;
    }; // namespace IAuthorization
} // namespace Server