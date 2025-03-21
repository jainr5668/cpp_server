#pragma once

#include <string>
#include <unordered_map>

namespace Server
{
    class IAuthentication
    {
        public:
        IAuthentication() = default;
        ~IAuthentication() = default;
        virtual std::string getAuthorizationToken() = 0;
        virtual std::unordered_map<std::string, std::string> getPayload() = 0;
        virtual bool isAuthenticated() = 0;
        virtual void setAuthorizationToken(const std::string authorization_token) = 0;
    }; // namespace IAuthentication
} // namespace Server