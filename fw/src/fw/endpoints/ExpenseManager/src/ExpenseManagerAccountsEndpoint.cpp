#include "ExpenseManagerAccountsEndpoint.h"
#include "ExpenseManagerAccountsServiceTypes.h"

using ExpenseManagerAccountsPostData = services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsPostData;
using ExpenseManagerAccountsPatchData = services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsPatchData;
namespace endpoints
{
    namespace ExpenseManager
    {
        ExpenseManagerAccountsEndpoint::ExpenseManagerAccountsEndpoint(endpoints::ExpenseManager::ExpenseManagerEndpointInjections *&injection)
        {
            logger_.info("ExpenseManagerAccountsEndpoint::ExpenseManagerAccountsEndpoint Entry");
            injections_ = injection;
            logger_.info("ExpenseManagerAccountsEndpoint::ExpenseManagerAccountsEndpoint Exit");
        }

        ExpenseManagerAccountsEndpoint::~ExpenseManagerAccountsEndpoint()
        {
            logger_.info("ExpenseManagerAccountsEndpoint::~ExpenseManagerAccountsEndpoint Entry");
            logger_.info("ExpenseManagerAccountsEndpoint::~ExpenseManagerAccountsEndpoint Exit");
        }

        void ExpenseManagerAccountsEndpoint::addAccount(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerAccountsEndpoint::addAccount Entry");
            for (auto &header : routeContext.req->headers){
                logger_.info("ExpenseManagerAccountsEndpoint::addAccount Header: " + header.first + " : " + header.second);
            }
            std::string userId = injections_->utilityService->getValueFromMap(*(routeContext.req->authorization->isAuthorized()), "userId", "");
            ExpenseManagerAccountsPostData account;
            bool isbodyValid = false;
            std::string errorMessage = "";
            try
            {
                account = jsonToObject<ExpenseManagerAccountsPostData>(routeContext.req->body);
                isbodyValid = true;
            }
            catch (const std::exception &e)
            {
                errorMessage = std::string(e.what());
                logger_.error("ExpenseManagerAccountsEndpoint::addAccount Error: " + errorMessage);
            }
            if (isbodyValid)
            {
                account.userId.value = userId;
                logger.info("ExpenseManagerAccountsEndpoint::addAccount userId: " + account.userId.value);
                auto result = injections_->accountsService_->createAccount(account);
                if (result.first)
                {
                    routeContext.res->status_code = 201;
                    routeContext.res->body = objectToJson(result.second);
                }
                else
                {
                    routeContext.res->status_code = 500;
                    routeContext.res->body = "Internal Server Error";
                }
            }
            else
            {
                routeContext.res->status_code = 400;
                routeContext.res->body = errorMessage;
            }
            logger_.info("ExpenseManagerAccountsEndpoint::addAccount Exit");
        }

        void ExpenseManagerAccountsEndpoint::connect()
        {
            logger_.info("ExpenseManagerAccountsEndpoint::connect Entry");
            logger_.info("ExpenseManagerAccountsEndpoint::connect Exit");
        }

        void ExpenseManagerAccountsEndpoint::deleteAccount(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerAccountsEndpoint::deleteAccount Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerAccountsEndpoint::deleteAccount Exit");
        }

        void ExpenseManagerAccountsEndpoint::getAccount(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerAccountsEndpoint::getAccount Entry");
            std::string userId = injections_->utilityService->getValueFromMap(*(routeContext.req->authorization->isAuthorized()), "userId", "");
            std::string accountId = routeContext.path_params.at("id");
            auto result = injections_->accountsService_->getAccount(userId, accountId);
            if (result.first)
            {
                routeContext.res->status_code = 200;
                routeContext.res->body = objectToJson(result.second);
            }
            else
            {
                routeContext.res->status_code = 500;
                routeContext.res->body = "Internal Server Error";
            }
            logger_.info("ExpenseManagerAccountsEndpoint::getAccount Exit");
        }

        void ExpenseManagerAccountsEndpoint::getAccounts(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerAccountsEndpoint::getAccounts Entry");
            std::string userId = injections_->utilityService->getValueFromMap(*(routeContext.req->authorization->isAuthorized()), "userId", "");
            auto result = injections_->accountsService_->getAccounts(userId);
            if (result.first)
            {
                routeContext.res->status_code = 200;
                routeContext.res->body = objectToJson(result.second);
            }
            else
            {
                routeContext.res->status_code = 500;
                routeContext.res->body = "Internal Server Error";
            }
            logger_.info("ExpenseManagerAccountsEndpoint::getAccounts Exit");
        }

        void *ExpenseManagerAccountsEndpoint::getInstance()
        {
            logger_.info("ExpenseManagerAccountsEndpoint::getInstance Entry");
            logger_.info("ExpenseManagerAccountsEndpoint::getInstance Exit");
            return this;
        }

        void *ExpenseManagerAccountsEndpoint::getInterface(ModuleUid uid)
        {
            logger_.info("ExpenseManagerAccountsEndpoint::getInterface Entry");
            void *interface = nullptr;
            if (uid == GET_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerAccountsEndpoint))
            {
                interface = this;
            }
            logger_.info("ExpenseManagerAccountsEndpoint::getInterface Exit");
            return interface;
        }

        void ExpenseManagerAccountsEndpoint::initialize()
        {
            logger_.info("ExpenseManagerAccountsEndpoint::initialize Entry");
            for (auto route : getRoutes())
            {
                addRoute(route);
            }
            logger_.info("ExpenseManagerAccountsEndpoint::initialize Exit");
        }

        void ExpenseManagerAccountsEndpoint::setInterface(ModuleUid uid, void *interface)
        {
            logger_.info("ExpenseManagerAccountsEndpoint::setInterface Entry");
            logger_.info("ExpenseManagerAccountsEndpoint::setInterface Exit");
        }

        void ExpenseManagerAccountsEndpoint::shutdown()
        {
            logger_.info("ExpenseManagerAccountsEndpoint::shutdown Entry");
            logger_.info("ExpenseManagerAccountsEndpoint::shutdown Exit");
        }

        void ExpenseManagerAccountsEndpoint::updateAccount(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerAccountsEndpoint::updateAccount Entry");
            std::string userId = injections_->utilityService->getValueFromMap(*(routeContext.req->authorization->isAuthorized()), "userId", "");
            std::string accountId = routeContext.path_params.at("id");
            ExpenseManagerAccountsPatchData account;
            bool isbodyValid = false;
            std::string errorMessage = "";
            try
            {
                account = jsonToObject<ExpenseManagerAccountsPatchData>(routeContext.req->body);
                isbodyValid = true;
            }
            catch (const std::exception &e)
            {
                errorMessage = std::string(e.what());
                logger_.error("ExpenseManagerAccountsEndpoint::addAccount Error: " + errorMessage);
            }
            if (isbodyValid)
            {
                auto result = injections_->accountsService_->updateAccount(userId, accountId, account);
                if (result.first)
                {
                    routeContext.res->status_code = 200;
                    routeContext.res->body = objectToJson(result.second);
                }
                else
                {
                    routeContext.res->status_code = 500;
                    routeContext.res->body = "Internal Server Error";
                }
            }
            else
            {
                routeContext.res->status_code = 400;
                routeContext.res->body = errorMessage;
            }
            logger_.info("ExpenseManagerAccountsEndpoint::updateAccount Exit");
        }

        std::vector<Route> ExpenseManagerAccountsEndpoint::getRoutes()
        {
            logger_.info("ExpenseManagerAccountsEndpoint::getRoutes Entry");
            std::vector<Route> routes;
            common::authorization::AuthorizationConfig getAccountsConfig, getAccountConfig, addAccountConfig;
            common::authorization::AuthorizationConfig updateAccountConfig, deleteAccountConfig;

            // Get Accounts
            getAccountsConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::GET, getAccountsConfig,
                                   std::bind(&ExpenseManagerAccountsEndpoint::getAccounts, this, std::placeholders::_1)});

            // Get Account
            getAccountConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::GET, getAccountConfig,
                                   std::bind(&ExpenseManagerAccountsEndpoint::getAccount, this, std::placeholders::_1)});

            // Add Account
            addAccountConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::POST, addAccountConfig,
                                   std::bind(&ExpenseManagerAccountsEndpoint::addAccount, this, std::placeholders::_1)});

            // Update Account
            updateAccountConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::PATCH, updateAccountConfig,
                                   std::bind(&ExpenseManagerAccountsEndpoint::updateAccount, this, std::placeholders::_1)});

            // Delete Account
            deleteAccountConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::DELETE, deleteAccountConfig,
                                   std::bind(&ExpenseManagerAccountsEndpoint::deleteAccount, this, std::placeholders::_1)});
            logger_.info("ExpenseManagerAccountsEndpoint::getRoutes Exit");

            for (auto route : routes)
            {
                routes.push_back(Route{route.path, RouteMethod::OPTIONS, deleteAccountConfig,
                                       std::bind(&BaseEndpoint::handlePreflight, this, std::placeholders::_1)});
            }
            return routes;
        }
    }
}
