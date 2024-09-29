#include "AuthenticationEndpoint.h"
#include "Authorization.h"
#include "AuthenticationServiceData.h"
#include "AuthorizationTypes.h"

using AuthenticationServiceInjections = services::AuthenticationService::AuthenticationServiceInjections;
using LoginData = services::AuthenticationService::AuthenticationServiceTypes::LoginData;
using LoginResponse = services::AuthenticationService::AuthenticationServiceTypes::LoginResponse;
using AuthorizationConfig = common::authorization::AuthorizationConfig;

namespace endpoints
{
    namespace AuthenticationEndpoint
    {
        AuthenticationEndpoint::AuthenticationEndpoint()
        {
            logger.info("AuthenticationEndpoint::AuthenticationEndpoint Entry");
            std::unique_ptr<AuthenticationServiceInjections> injections_ = std::make_unique<AuthenticationServiceInjections>();
            std::unique_ptr<Data> data = std::make_unique<Data>("AuthenticationServiceData.db");
            auto authenticationServiceData_ = std::make_unique<services::AuthenticationService::AuthenticationServiceData>(std::move(data));
            injections_->authenticationServiceData_ = std::move(authenticationServiceData_);
            authenticationService = new services::AuthenticationService::AuthenticationService(std::move(injections_));
            for (auto route : getRoutes())
            {
                addRoute(route);
            }
            logger.info("AuthenticationEndpoint::AuthenticationEndpoint Exit");
        }
        void AuthenticationEndpoint::login(RouteContext routeContext)
        {
            logger.info("AuthenticationEndpoint::login Entry");
            std::string userId = authenticationService->isCredValid(jsonToObject<LoginData>(routeContext.req->body));
            if (!userId.empty())
            {
                routeContext.res->status_code = 200;
                services::AuthenticationService::AuthenticationServiceTypes::LoginResponse loginResponse;
                Authorization authorization;
                std::unordered_map<std::string, std::string> payload;
                payload.insert(std::make_pair("scope", "api"));
                payload.insert(std::make_pair("userId", userId));
                payload.insert(std::make_pair("accessLevel", "admin")); // This should be fetched from DB
                loginResponse.access_token.value = authorization.createToken(payload);
                loginResponse.message.value = "Login Success";
                routeContext.res->body = objectToJson(loginResponse);
            }
            else
            {
                routeContext.res->status_code = 401;
                routeContext.res->body = "Unauthorized";
            }
            logger.info("AuthenticationEndpoint::login Exit");
        }

        void AuthenticationEndpoint::signup(RouteContext routeContext)
        {
            logger.info("AuthenticationEndpoint::signup Entry");
            bool isUserCreated = authenticationService->createUser(jsonToObject<services::AuthenticationService::AuthenticationServiceTypes::SingupData>(routeContext.req->body));
            if (isUserCreated)
            {
                routeContext.res->status_code = 200;
                routeContext.res->body = "User Created";
            }
            else
            {
                routeContext.res->status_code = 409;
                routeContext.res->body = "User Already Exists";
            }
            logger.info("AuthenticationEndpoint::signup Exit");
        }

        void AuthenticationEndpoint::timepass(RouteContext routeContext)
        {
            logger.info("AuthenticationEndpoint::timepass Entry");
            routeContext.res->status_code = 200;
            routeContext.res->body = "Timepass";
            logger.info("AuthenticationEndpoint::timepass Exit");
        }
        std::vector<Route> AuthenticationEndpoint::getRoutes()
        {
            logger.info("AuthenticationEndpoint::getRoutes Entry");
            std::vector<Route> routes;
            AuthorizationConfig loginConfig, signupConfig, timepassConfig;

            // Login endpoint
            loginConfig.enabled = false;
            routes.push_back(Route{"login", RouteMethod::POST, loginConfig,
                                   std::function<void(RouteContext)>(std::bind(&AuthenticationEndpoint::login, this, std::placeholders::_1))});

            // Signup endpoint
            signupConfig.enabled = false;
            routes.push_back(Route{"signup", RouteMethod::POST, signupConfig,
                                   std::function<void(RouteContext)>(std::bind(&AuthenticationEndpoint::signup, this, std::placeholders::_1))});

            // Timepass endpoint
            timepassConfig.enabled = true;
            timepassConfig.accessLevels.push_back("admin");
            timepassConfig.scope.push_back("api");
            routes.push_back(Route{"timepass", RouteMethod::GET, timepassConfig,
                                   std::function<void(RouteContext)>(std::bind(&AuthenticationEndpoint::timepass, this, std::placeholders::_1))});

            logger.info("AuthenticationEndpoint::getRoutes total routes: " + std::to_string(routes.size()));
            logger.info("AuthenticationEndpoint::getRoutes Exit");
            return routes;
        }
    }
} // namespace endpoints::AuthenticationEndpoint