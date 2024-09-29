#pragma once
#include <memory>
#include "logger.h"

namespace endpoints
{
    namespace AuthenticationEndpoint
    {
        class AuthenticationEndpointInjections
        {
        public:
            AuthenticationEndpointInjections() = default;
            ~AuthenticationEndpointInjections() = default;
            std::shared_ptr<Logger> logger{nullptr};
        };
    } // namespace endpoints::AuthenticationEndpoint
} // namespace endpoints