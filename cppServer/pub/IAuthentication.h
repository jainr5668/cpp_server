#pragma once

#include <string>
#include <unordered_map>
#include "IAuthorization.h"
#include <memory>

using IAuthorization = Server::IAuthorization;
namespace Server
{
    class IAuthentication
    {
        public:
        IAuthentication() = default;
        ~IAuthentication() = default;
        virtual std::unique_ptr<IAuthorization> getAuthorization(std::string token) = 0;
    }; // namespace IAuthentication
} // namespace Server