#ifndef AUTHENTICATIONENDPOINT_H
#define AUTHENTICATIONENDPOINT_H
#include "IAuthenticationEndpoint.h"
#include "logger.h"
#include "RouterType.h"
#include "AuthenticationService.h"
#include "AuthenticationEndpointInjections.h"
#include <memory>
#include "BaseService.h"

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
            void logoutUser(RouteContext routeContext);
            void initialize();
            void *getInterface(ModuleUid uid);
            void setInterface(ModuleUid uid, void *interface);
            void connect();
            void *getInstance();
            void shutdown();
            ModuleUid getInterfaceUID(){return GET_MODULE_UID(endpoints::AuthenticationEndpoint::IAuthenticationEndpoint);};

        private:
            Logger logger;
            AuthenticationEndpointInjections* injections_{nullptr};

            /**
             * @brief Get the vector of Routes object
             */
            std::vector<Route> getRoutes();
        };
    }
} // namespace endpoints::AuthenticationEndpoint
#endif // AUTHENTICATIONENDPOINT_H
