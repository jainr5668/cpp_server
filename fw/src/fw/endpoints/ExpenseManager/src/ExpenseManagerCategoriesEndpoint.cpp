#include "ExpenseManagerCategoriesEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        ExpenseManagerCategoriesEndpoint::ExpenseManagerCategoriesEndpoint(endpoints::ExpenseManager::ExpenseManagerInjections* &injection)
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::ExpenseManagerCategoriesEndpoint Entry");
            injections_ = injection;
            logger_.info("ExpenseManagerCategoriesEndpoint::ExpenseManagerCategoriesEndpoint Exit");
        }

        ExpenseManagerCategoriesEndpoint::~ExpenseManagerCategoriesEndpoint()
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::~ExpenseManagerCategoriesEndpoint Entry");
            logger_.info("ExpenseManagerCategoriesEndpoint::~ExpenseManagerCategoriesEndpoint Exit");
        }

        void ExpenseManagerCategoriesEndpoint::getCategories(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::getCategories Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerCategoriesEndpoint::getCategories Exit");
        }

        void ExpenseManagerCategoriesEndpoint::addCategory(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::addCategory Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerCategoriesEndpoint::addCategory Exit");
        }

        void ExpenseManagerCategoriesEndpoint::updateCategory(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::updateCategory Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerCategoriesEndpoint::updateCategory Exit");
        }

        void ExpenseManagerCategoriesEndpoint::deleteCategory(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::deleteCategory Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerCategoriesEndpoint::deleteCategory Exit");
        }

        void ExpenseManagerCategoriesEndpoint::connect()
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::connect Entry");
            logger_.info("ExpenseManagerCategoriesEndpoint::connect Exit");
        }

        void ExpenseManagerCategoriesEndpoint::initialize()
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::initialize Entry");
            for(auto &route : getRoutes())
            {
                addRoute(route);
            }
            logger_.info("ExpenseManagerCategoriesEndpoint::initialize Exit");
        }

        void *ExpenseManagerCategoriesEndpoint::getInstance()
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::getInstance Entry");
            logger_.info("ExpenseManagerCategoriesEndpoint::getInstance Exit");
            return this;
        }

        void *ExpenseManagerCategoriesEndpoint::getInterface(ModuleUid uid)
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::getInterface Entry");
            void *interface = nullptr;
            if(uid == GET_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerCategoriesEndpoint))
            {
                interface = this;
            }
            logger_.info("ExpenseManagerCategoriesEndpoint::getInterface Exit");
            return interface;
        }

        void ExpenseManagerCategoriesEndpoint::setInterface(ModuleUid uid, void *interface)
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::setInterface Entry");
            logger_.info("ExpenseManagerCategoriesEndpoint::setInterface Exit");
        }

        void ExpenseManagerCategoriesEndpoint::shutdown()
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::shutdown Entry");
            logger_.info("ExpenseManagerCategoriesEndpoint::shutdown Exit");
        }

        std::vector<Route> ExpenseManagerCategoriesEndpoint::getRoutes()
        {
            logger_.info("ExpenseManagerCategoriesEndpoint::getRoutes Entry");
            std::vector<Route> routes;
            common::authorization::AuthorizationConfig getCategoriesConfig, addCategoryConfig, updateCategoryConfig, deleteCategoryConfig;

            // Get Categories
            getCategoriesConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::GET, getCategoriesConfig,
                std::bind(&ExpenseManagerCategoriesEndpoint::getCategories, this, std::placeholders::_1)});

            // Add Category
            addCategoryConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::POST, addCategoryConfig,
                std::bind(&ExpenseManagerCategoriesEndpoint::addCategory, this, std::placeholders::_1)});

            // Update Category
            updateCategoryConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::PUT, updateCategoryConfig,
                std::bind(&ExpenseManagerCategoriesEndpoint::updateCategory, this, std::placeholders::_1)});

            // Delete Category
            deleteCategoryConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::DELETE, deleteCategoryConfig,
                std::bind(&ExpenseManagerCategoriesEndpoint::deleteCategory, this, std::placeholders::_1)});

            for(auto &route : routes)
            {
                routes.push_back(Route{route.path, RouteMethod::OPTIONS, deleteCategoryConfig,
                    std::bind(&BaseEndpoint::handlePreflight, this, std::placeholders::_1)});
            }

            logger_.info("ExpenseManagerCategoriesEndpoint::getRoutes Exit");
            return routes;
        }
    }
}