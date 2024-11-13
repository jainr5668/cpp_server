#include "AuthenticationEndpoint.h"
#include "Authorization.h"
#include "AuthenticationServiceData.h"
#include "AuthorizationTypes.h"

using AuthenticationServiceInjections = services::AuthenticationService::AuthenticationServiceInjections;
using AuthorizationConfig = common::authorization::AuthorizationConfig;
using IAuthenticationService = services::AuthenticationService::IAuthenticationService;
using LoginData = services::AuthenticationService::AuthenticationServiceTypes::LoginData;
using LoginResponse = services::AuthenticationService::AuthenticationServiceTypes::LoginResponse;
using SingupData = services::AuthenticationService::AuthenticationServiceTypes::SingupData;

namespace endpoints
{
    namespace AuthenticationEndpoint
    {
        AuthenticationEndpoint::AuthenticationEndpoint()
        {
            logger.info("AuthenticationEndpoint::AuthenticationEndpoint Entry");

            logger.info("AuthenticationEndpoint::AuthenticationEndpoint Exit");
        }
        void AuthenticationEndpoint::initialize()
        {
            logger.info("AuthenticationEndpoint::initialize Entry");
            injections_ = new AuthenticationEndpointInjections();
            for (auto route : getRoutes())
            {
                addRoute(route);
            }
            logger.info("AuthenticationEndpoint::initialize Exit");
        }
        void *AuthenticationEndpoint::getInterface(ModuleUid uid)
        {
            logger.info("AuthenticationEndpoint::getInterface Entry");
            logger.info("AuthenticationEndpoint::getInterface Exit");
            return dynamic_cast<IAuthenticationEndpoint *>(this);
        }
        void AuthenticationEndpoint::setInterface(ModuleUid uid, void *interface)
        {
            logger.info("AuthenticationEndpoint::setInterface Entry");
            if (uid == GET_MODULE_UID(IAuthenticationService))
            {
                injections_->authenticationService = std::shared_ptr<IAuthenticationService>(static_cast<IAuthenticationService *>(interface));
            }
            else if (uid == GET_MODULE_UID(services::CommonService::IUtilityService))
            {
                injections_->utilityService = std::shared_ptr<services::CommonService::IUtilityService>(static_cast<services::CommonService::IUtilityService *>(interface));
            }
            logger.info("AuthenticationEndpoint::setInterface Exit");
        }
        void AuthenticationEndpoint::connect()
        {
            logger.info("AuthenticationEndpoint::connect Entry");
            assert(injections_->authenticationService != nullptr), "Authentication Service is not set";
            assert(injections_->utilityService != nullptr), "Utility Service is not set";
            logger.info("AuthenticationEndpoint::connect Exit");
        }
        void *AuthenticationEndpoint::getInstance()
        {
            logger.info("AuthenticationEndpoint::getInstance Entry");
            logger.info("AuthenticationEndpoint::getInstance Exit");
            return nullptr;
        }
        void AuthenticationEndpoint::shutdown()
        {
            logger.info("AuthenticationEndpoint::shutdown Entry");
            // delete injections_;
            logger.info("AuthenticationEndpoint::shutdown Exit");
        }

        void AuthenticationEndpoint::login(RouteContext routeContext)
        {
            logger.info("AuthenticationEndpoint::login Entry");
            LoginData jData = jsonToObject<LoginData>(routeContext.req->body);
            logger.info("AuthenticationEndpoint::login User: " + jData.username.value);
            std::string userId = injections_->authenticationService->isCredValid(jData);
            if (!userId.empty())
            {
                routeContext.res->status_code = 200;
                LoginResponse loginResponse;
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
            updateCorsHeaders(routeContext);

            SingupData jsonObject_;
            try{
                jsonObject_ = jsonToObject<SingupData>(routeContext.req->body);
            }
            catch(const std::exception& e){
                routeContext.res->status_code = 400;
                routeContext.res->body = e.what();
                return;
            }
            if (jsonObject_.username.value.empty() || jsonObject_.password.value.empty())
            {
                routeContext.res->status_code = 400;
                routeContext.res->body = "Required data missing.";
            }
            else
            {
                bool isUserCreated = injections_->authenticationService->createUser(jsonObject_);
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

        void AuthenticationEndpoint::handlePreflight(RouteContext routeContext)
        {
            logger.info("AuthenticationEndpoint::handlePreflight Entry");
            routeContext.res->headers.insert({"Access-Control-Allow-Origin", "*"});
            routeContext.res->headers.insert({"Access-Control-Allow-Methods", "GET, POST, OPTIONS"});
            routeContext.res->headers.insert({"Access-Control-Allow-Headers", "Content-Type, Authorization"});
            routeContext.res->status_code = 204; // No Content
            routeContext.res->body = "";
            logger.info("AuthenticationEndpoint::handlePreflight Exit");
        }

        void AuthenticationEndpoint::updateCorsHeaders(RouteContext &routeContext){
            logger.info("AuthenticationEndpoint::updateCorsHeaders Entry");
            auto host = injections_->utilityService->getValueFromMap(routeContext.req->headers, "Host", "");
            auto origin = injections_->utilityService->getValueFromMap(routeContext.req->headers, "Origin", "");
            if (origin.empty())
            {
                origin = host;
            }
            if (host != origin)
            {
                routeContext.res->headers.insert({"Access-Control-Allow-Origin", "*"});
                routeContext.res->headers.insert({"Access-Control-Allow-Methods", "GET, POST, OPTIONS"});
                routeContext.res->headers.insert({"Access-Control-Allow-Headers", "Content-Type, Authorization"});
            }
            logger.info("AuthenticationEndpoint::updateCorsHeaders Exit");
            routeContext;
        }
        std::vector<Route> AuthenticationEndpoint::getRoutes()
        {
            logger.info("AuthenticationEndpoint::getRoutes Entry");
            std::vector<Route> routes;
            AuthorizationConfig loginConfig, signupConfig, timepassConfig, preflightConfig;

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

            // Preflight endpoint
            preflightConfig.enabled = false;
            for (auto &route : routes)
            {
                routes.push_back(Route{route.path, RouteMethod::OPTIONS, preflightConfig,
                                       std::function<void(RouteContext)>(std::bind(&AuthenticationEndpoint::handlePreflight, this, std::placeholders::_1))});
            }

            logger.info("AuthenticationEndpoint::getRoutes total routes: " + std::to_string(routes.size()));
            logger.info("AuthenticationEndpoint::getRoutes Exit");
            return routes;
        }
    }
} // namespace endpoints::AuthenticationEndpoint