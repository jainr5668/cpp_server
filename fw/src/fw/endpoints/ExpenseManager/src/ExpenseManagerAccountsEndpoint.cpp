#include "ExpenseManagerAccountsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        ExpenseManagerAccountsEndpoint::ExpenseManagerAccountsEndpoint(endpoints::ExpenseManager::ExpenseManagerInjections* &injection)
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
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
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
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerAccountsEndpoint::getAccount Exit");
        }

        void ExpenseManagerAccountsEndpoint::getAccounts(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerAccountsEndpoint::getAccounts Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
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
            if(uid == GET_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerAccountsEndpoint))
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
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerAccountsEndpoint::updateAccount Exit");
        }

        std::vector<Route> ExpenseManagerAccountsEndpoint::getRoutes(){
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

            for(auto route : routes){
                routes.push_back(Route{route.path, RouteMethod::OPTIONS, deleteAccountConfig,
                    std::bind(&BaseEndpoint::handlePreflight, this, std::placeholders::_1)});
            }
            return routes;
        }
    }
}