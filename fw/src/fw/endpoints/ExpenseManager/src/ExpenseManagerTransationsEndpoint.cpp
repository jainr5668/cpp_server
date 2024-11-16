#include "ExpenseManagerTransationsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        ExpenseManagerTransationsEndpoint::ExpenseManagerTransationsEndpoint(endpoints::ExpenseManager::ExpenseManagerInjections* &injection)
        {
            logger_.info("ExpenseManagerTransationsEndpoint::ExpenseManagerTransationsEndpoint Entry");
            injections_ = injection;
            logger_.info("ExpenseManagerTransationsEndpoint::ExpenseManagerTransationsEndpoint Exit");
        }

        ExpenseManagerTransationsEndpoint::~ExpenseManagerTransationsEndpoint()
        {
            logger_.info("ExpenseManagerTransationsEndpoint::~ExpenseManagerTransationsEndpoint Entry");
            logger_.info("ExpenseManagerTransationsEndpoint::~ExpenseManagerTransationsEndpoint Exit");
        }

        void ExpenseManagerTransationsEndpoint::addTransation(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTransationsEndpoint::addTransation Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTransationsEndpoint::addTransation Exit");
        }

        void ExpenseManagerTransationsEndpoint::connect()
        {
            logger_.info("ExpenseManagerTransationsEndpoint::connect Entry");
            logger_.info("ExpenseManagerTransationsEndpoint::connect Exit");
        }

        void ExpenseManagerTransationsEndpoint::deleteTransation(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTransationsEndpoint::deleteTransation Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTransationsEndpoint::deleteTransation Exit");
        }

        void ExpenseManagerTransationsEndpoint::getTransation(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTransationsEndpoint::getTransation Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTransationsEndpoint::getTransation Exit");
        }

        void ExpenseManagerTransationsEndpoint::getTransations(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTransationsEndpoint::getTransations Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTransationsEndpoint::getTransations Exit");
        }

        void *ExpenseManagerTransationsEndpoint::getInstance()
        {
            logger_.info("ExpenseManagerTransationsEndpoint::getInstance Entry");
            logger_.info("ExpenseManagerTransationsEndpoint::getInstance Exit");
            return this;
        }

        void *ExpenseManagerTransationsEndpoint::getInterface(ModuleUid uid)
        {
            logger_.info("ExpenseManagerTransationsEndpoint::getInterface Entry");
            void *interface = nullptr;
            if(uid == GET_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerTransationsEndpoint))
            {
                interface = this;
            }
            logger_.info("ExpenseManagerTransationsEndpoint::getInterface Exit");
            return interface;
        }

        void ExpenseManagerTransationsEndpoint::initialize()
        {
            logger_.info("ExpenseManagerTransationsEndpoint::initialize Entry");
            for (auto route : getRoutes())
            {
                addRoute(route);
            }
            logger_.info("ExpenseManagerTransationsEndpoint::initialize Exit");
        }

        void ExpenseManagerTransationsEndpoint::setInterface(ModuleUid uid, void *interface)
        {
            logger_.info("ExpenseManagerTransationsEndpoint::setInterface Entry");
            logger_.info("ExpenseManagerTransationsEndpoint::setInterface Exit");
        }

        void ExpenseManagerTransationsEndpoint::shutdown()
        {
            logger_.info("ExpenseManagerTransationsEndpoint::shutdown Entry");
            logger_.info("ExpenseManagerTransationsEndpoint::shutdown Exit");
        }

        void ExpenseManagerTransationsEndpoint::updateTransation(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTransationsEndpoint::updateTransation Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTransationsEndpoint::updateTransation Exit");
        }

        std::vector<Route> ExpenseManagerTransationsEndpoint::getRoutes(){
            logger_.info("ExpenseManagerTransationsEndpoint::getRoutes Entry");
            std::vector<Route> routes;
            common::authorization::AuthorizationConfig getTransationsConfig, getTransationConfig, addTransationConfig, updateTransationConfig, deleteTransationConfig;

            // Get Transations
            getTransationsConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::GET, getTransationsConfig, std::bind(&ExpenseManagerTransationsEndpoint::getTransations, this, std::placeholders::_1)});

            // Get Transation
            getTransationConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::GET, getTransationConfig, std::bind(&ExpenseManagerTransationsEndpoint::getTransation, this, std::placeholders::_1)});

            // Add Transation
            addTransationConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::POST, addTransationConfig, std::bind(&ExpenseManagerTransationsEndpoint::addTransation, this, std::placeholders::_1)});

            // Update Transation
            updateTransationConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::PATCH, updateTransationConfig, std::bind(&ExpenseManagerTransationsEndpoint::updateTransation, this, std::placeholders::_1)});

            // Delete Transation
            deleteTransationConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::DELETE, deleteTransationConfig, std::bind(&ExpenseManagerTransationsEndpoint::deleteTransation, this, std::placeholders::_1)});
            logger_.info("ExpenseManagerTransationsEndpoint::getRoutes Exit");

            for(auto route : routes){
                routes.push_back(Route{route.path, RouteMethod::OPTIONS, deleteTransationConfig, std::bind(&BaseEndpoint::handlePreflight, this, std::placeholders::_1)});
            }
            return routes;
        }
    }
}