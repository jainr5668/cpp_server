#pragma once
#include <vector>
#include <string>
namespace common
{
    namespace authorization
    {
        enum class AccessLevel
        {
            admin,
            user
        };
        struct AuthorizationConfig
        {
            bool enabled;
            std::vector<std::string> accessLevels;
            std::vector<std::string> scope;
        };
    }
}