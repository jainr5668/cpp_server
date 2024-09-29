#pragma once
#include "IAuthenticationEndpoint.h"
#include "logger.h"
#include "RouterType.h"
#include "AuthenticationService.h"
#include "AuthenticationServiceInjections.h"
#include <memory>

namespace endpoints
{
    namespace AuthenticationEndpoint
    {
        class AuthenticationEndpoint : public endpoints::AuthenticationEndpoint::IAuthenticationEndpoint
        {
        public:
            AuthenticationEndpoint();
            /**
             * @brief login
             * @param routeContext
             */
            void login(RouteContext routeContext);

            /**
             * @brief signup
             * @param routeContext
             */
            void signup(RouteContext routeContext);

            /**
             * @brief timepass
             * @param routeContext
             */
            void timepass(RouteContext routeContext);

        private:
            Logger logger;

            // Instance of AuthenticationService
            services::AuthenticationService::AuthenticationService *authenticationService;

            /**
             * @brief Get the vector of Routes object
             */
            std::vector<Route> getRoutes();
        };
    }
} // namespace endpoints::AuthenticationEndpoint