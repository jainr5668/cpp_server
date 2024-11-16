#include "ExpenseManagerTransactionsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        ExpenseManagerTransactionsEndpoint::ExpenseManagerTransactionsEndpoint(endpoints::ExpenseManager::ExpenseManagerInjections* &injection)
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::ExpenseManagerTransactionsEndpoint Entry");
            injections_ = injection;
            logger_.info("ExpenseManagerTransactionsEndpoint::ExpenseManagerTransactionsEndpoint Exit");
        }

        ExpenseManagerTransactionsEndpoint::~ExpenseManagerTransactionsEndpoint()
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::~ExpenseManagerTransactionsEndpoint Entry");
            logger_.info("ExpenseManagerTransactionsEndpoint::~ExpenseManagerTransactionsEndpoint Exit");
        }

        void ExpenseManagerTransactionsEndpoint::addTransaction(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::addTransaction Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTransactionsEndpoint::addTransaction Exit");
        }

        void ExpenseManagerTransactionsEndpoint::connect()
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::connect Entry");
            logger_.info("ExpenseManagerTransactionsEndpoint::connect Exit");
        }

        void ExpenseManagerTransactionsEndpoint::deleteTransaction(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::deleteTransaction Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTransactionsEndpoint::deleteTransaction Exit");
        }

        void ExpenseManagerTransactionsEndpoint::getTransaction(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::getTransaction Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTransactionsEndpoint::getTransaction Exit");
        }

        void ExpenseManagerTransactionsEndpoint::getTransactions(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::getTransactions Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTransactionsEndpoint::getTransactions Exit");
        }

        void *ExpenseManagerTransactionsEndpoint::getInstance()
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::getInstance Entry");
            logger_.info("ExpenseManagerTransactionsEndpoint::getInstance Exit");
            return this;
        }

        void *ExpenseManagerTransactionsEndpoint::getInterface(ModuleUid uid)
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::getInterface Entry");
            void *interface = nullptr;
            if(uid == GET_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerTransactionsEndpoint))
            {
                interface = this;
            }
            logger_.info("ExpenseManagerTransactionsEndpoint::getInterface Exit");
            return interface;
        }

        void ExpenseManagerTransactionsEndpoint::initialize()
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::initialize Entry");
            for (auto route : getRoutes())
            {
                addRoute(route);
            }
            logger_.info("ExpenseManagerTransactionsEndpoint::initialize Exit");
        }

        void ExpenseManagerTransactionsEndpoint::setInterface(ModuleUid uid, void *interface)
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::setInterface Entry");
            logger_.info("ExpenseManagerTransactionsEndpoint::setInterface Exit");
        }

        void ExpenseManagerTransactionsEndpoint::shutdown()
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::shutdown Entry");
            logger_.info("ExpenseManagerTransactionsEndpoint::shutdown Exit");
        }

        void ExpenseManagerTransactionsEndpoint::updateTransaction(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTransactionsEndpoint::updateTransaction Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTransactionsEndpoint::updateTransaction Exit");
        }

        std::vector<Route> ExpenseManagerTransactionsEndpoint::getRoutes(){
            logger_.info("ExpenseManagerTransactionsEndpoint::getRoutes Entry");
            std::vector<Route> routes;
            common::authorization::AuthorizationConfig getTransactionsConfig, getTransactionConfig, addTransactionConfig, updateTransactionConfig, deleteTransactionConfig;

            // Get Transactions
            getTransactionsConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::GET, getTransactionsConfig, std::bind(&ExpenseManagerTransactionsEndpoint::getTransactions, this, std::placeholders::_1)});

            // Get Transaction
            getTransactionConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::GET, getTransactionConfig, std::bind(&ExpenseManagerTransactionsEndpoint::getTransaction, this, std::placeholders::_1)});

            // Add Transaction
            addTransactionConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::POST, addTransactionConfig, std::bind(&ExpenseManagerTransactionsEndpoint::addTransaction, this, std::placeholders::_1)});

            // Update Transaction
            updateTransactionConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::PATCH, updateTransactionConfig, std::bind(&ExpenseManagerTransactionsEndpoint::updateTransaction, this, std::placeholders::_1)});

            // Delete Transaction
            deleteTransactionConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::DELETE, deleteTransactionConfig, std::bind(&ExpenseManagerTransactionsEndpoint::deleteTransaction, this, std::placeholders::_1)});
            logger_.info("ExpenseManagerTransactionsEndpoint::getRoutes Exit");

            for(auto route : routes){
                routes.push_back(Route{route.path, RouteMethod::OPTIONS, deleteTransactionConfig, std::bind(&BaseEndpoint::handlePreflight, this, std::placeholders::_1)});
            }
            return routes;
        }
    }
}