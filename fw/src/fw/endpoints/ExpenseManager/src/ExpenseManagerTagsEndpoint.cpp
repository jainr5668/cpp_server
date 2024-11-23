#include "ExpenseManagerTagsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        ExpenseManagerTagsEndpoint::ExpenseManagerTagsEndpoint(endpoints::ExpenseManager::ExpenseManagerInjections* &injection)
        {
            logger_.info("ExpenseManagerTagsEndpoint::ExpenseManagerTagsEndpoint Entry");
            injections_ = injection;
            logger_.info("ExpenseManagerTagsEndpoint::ExpenseManagerTagsEndpoint Exit");
        }

        ExpenseManagerTagsEndpoint::~ExpenseManagerTagsEndpoint()
        {
            logger_.info("ExpenseManagerTagsEndpoint::~ExpenseManagerTagsEndpoint Entry");
            logger_.info("ExpenseManagerTagsEndpoint::~ExpenseManagerTagsEndpoint Exit");
        }

        void ExpenseManagerTagsEndpoint::addTag(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTagsEndpoint::addTag Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTagsEndpoint::addTag Exit");
        }

        void ExpenseManagerTagsEndpoint::connect()
        {
            logger_.info("ExpenseManagerTagsEndpoint::connect Entry");
            logger_.info("ExpenseManagerTagsEndpoint::connect Exit");
        }

        void ExpenseManagerTagsEndpoint::deleteTag(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTagsEndpoint::deleteTag Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTagsEndpoint::deleteTag Exit");
        }

        void ExpenseManagerTagsEndpoint::getTag(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTagsEndpoint::getTag Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTagsEndpoint::getTag Exit");
        }

        void ExpenseManagerTagsEndpoint::getTags(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTagsEndpoint::getTags Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTagsEndpoint::getTags Exit");
        }

        void *ExpenseManagerTagsEndpoint::getInstance()
        {
            logger_.info("ExpenseManagerTagsEndpoint::getInstance Entry");
            logger_.info("ExpenseManagerTagsEndpoint::getInstance Exit");
            return this;
        }

        void *ExpenseManagerTagsEndpoint::getInterface(ModuleUid uid)
        {
            logger_.info("ExpenseManagerTagsEndpoint::getInterface Entry");
            void *interface = nullptr;
            if(uid == GET_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerTagsEndpoint))
            {
                interface = this;
            }
            logger_.info("ExpenseManagerTagsEndpoint::getInterface Exit");
            return interface;
        }

        void ExpenseManagerTagsEndpoint::initialize()
        {
            logger_.info("ExpenseManagerTagsEndpoint::initialize Entry");
            for (auto route : getRoutes())
            {
                addRoute(route);
            }
            logger_.info("ExpenseManagerTagsEndpoint::initialize Exit");
        }

        void ExpenseManagerTagsEndpoint::setInterface(ModuleUid uid, void *interface)
        {
            logger_.info("ExpenseManagerTagsEndpoint::setInterface Entry");
            logger_.info("ExpenseManagerTagsEndpoint::setInterface Exit");
        }

        void ExpenseManagerTagsEndpoint::shutdown()
        {
            logger_.info("ExpenseManagerTagsEndpoint::shutdown Entry");
            logger_.info("ExpenseManagerTagsEndpoint::shutdown Exit");
        }

        void ExpenseManagerTagsEndpoint::updateTag(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerTagsEndpoint::updateTag Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerTagsEndpoint::updateTag Exit");
        }

        std::vector<Route> ExpenseManagerTagsEndpoint::getRoutes(){
            logger_.info("ExpenseManagerTagsEndpoint::getRoutes Entry");
            std::vector<Route> routes;
            common::authorization::AuthorizationConfig getTagsConfig, getTagConfig, addTagConfig, updateTagConfig, deleteTagConfig;

            // Get Tags
            getTagsConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::GET, getTagsConfig,
                std::bind(&ExpenseManagerTagsEndpoint::getTags, this, std::placeholders::_1)});

            // Get Tag
            getTagConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::GET, getTagConfig,
                std::bind(&ExpenseManagerTagsEndpoint::getTag, this, std::placeholders::_1)});

            // Add Tag
            addTagConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::POST, addTagConfig,
                std::bind(&ExpenseManagerTagsEndpoint::addTag, this, std::placeholders::_1)});

            // Update Tag
            updateTagConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::PATCH, updateTagConfig,
                std::bind(&ExpenseManagerTagsEndpoint::updateTag, this, std::placeholders::_1)});

            // Delete Tag
            deleteTagConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::DELETE, deleteTagConfig,
                std::bind(&ExpenseManagerTagsEndpoint::deleteTag, this, std::placeholders::_1)});
            logger_.info("ExpenseManagerTagsEndpoint::getRoutes Exit");

            for(auto route : routes){
                routes.push_back(Route{route.path, RouteMethod::OPTIONS, deleteTagConfig,
                    std::bind(&BaseEndpoint::handlePreflight, this, std::placeholders::_1)});
            }
            return routes;
        }
    }
}