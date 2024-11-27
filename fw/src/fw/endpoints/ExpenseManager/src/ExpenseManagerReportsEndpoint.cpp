#include "ExpenseManagerReportsEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        ExpenseManagerReportsEndpoint::ExpenseManagerReportsEndpoint(endpoints::ExpenseManager::ExpenseManagerEndpointInjections* &injection)
        {
            logger_.info("ExpenseManagerReportsEndpoint::ExpenseManagerReportsEndpoint Entry");
            injections_ = injection;
            logger_.info("ExpenseManagerReportsEndpoint::ExpenseManagerReportsEndpoint Exit");
        }

        ExpenseManagerReportsEndpoint::~ExpenseManagerReportsEndpoint()
        {
            logger_.info("ExpenseManagerReportsEndpoint::~ExpenseManagerReportsEndpoint Entry");
            logger_.info("ExpenseManagerReportsEndpoint::~ExpenseManagerReportsEndpoint Exit");
        }

        void ExpenseManagerReportsEndpoint::addReport(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerReportsEndpoint::addReport Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerReportsEndpoint::addReport Exit");
        }

        void ExpenseManagerReportsEndpoint::connect()
        {
            logger_.info("ExpenseManagerReportsEndpoint::connect Entry");
            logger_.info("ExpenseManagerReportsEndpoint::connect Exit");
        }

        void ExpenseManagerReportsEndpoint::deleteReport(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerReportsEndpoint::deleteReport Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerReportsEndpoint::deleteReport Exit");
        }

        void ExpenseManagerReportsEndpoint::getReport(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerReportsEndpoint::getReport Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerReportsEndpoint::getReport Exit");
        }

        void ExpenseManagerReportsEndpoint::getReports(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerReportsEndpoint::getReports Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerReportsEndpoint::getReports Exit");
        }

        void *ExpenseManagerReportsEndpoint::getInstance()
        {
            logger_.info("ExpenseManagerReportsEndpoint::getInstance Entry");
            logger_.info("ExpenseManagerReportsEndpoint::getInstance Exit");
            return this;
        }

        void *ExpenseManagerReportsEndpoint::getInterface(ModuleUid uid)
        {
            logger_.info("ExpenseManagerReportsEndpoint::getInterface Entry");
            void *interface = nullptr;
            if(uid == GET_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerReportsEndpoint))
            {
                interface = this;
            }
            logger_.info("ExpenseManagerReportsEndpoint::getInterface Exit");
            return interface;
        }

        void ExpenseManagerReportsEndpoint::initialize()
        {
            logger_.info("ExpenseManagerReportsEndpoint::initialize Entry");
            for (auto route : getRoutes())
            {
                addRoute(route);
            }
            logger_.info("ExpenseManagerReportsEndpoint::initialize Exit");
        }

        void ExpenseManagerReportsEndpoint::setInterface(ModuleUid uid, void *interface)
        {
            logger_.info("ExpenseManagerReportsEndpoint::setInterface Entry");
            logger_.info("ExpenseManagerReportsEndpoint::setInterface Exit");
        }

        void ExpenseManagerReportsEndpoint::shutdown()
        {
            logger_.info("ExpenseManagerReportsEndpoint::shutdown Entry");
            logger_.info("ExpenseManagerReportsEndpoint::shutdown Exit");
        }

        void ExpenseManagerReportsEndpoint::updateReport(RouteContext routeContext)
        {
            logger_.info("ExpenseManagerReportsEndpoint::updateReport Entry");
            routeContext.res->status_code = 500;
            routeContext.res->body = "Not Implemented";
            logger_.info("ExpenseManagerReportsEndpoint::updateReport Exit");
        }

        std::vector<Route> ExpenseManagerReportsEndpoint::getRoutes(){
            logger_.info("ExpenseManagerReportsEndpoint::getRoutes Entry");
            std::vector<Route> routes;
            common::authorization::AuthorizationConfig getReportsConfig, getReportConfig, addReportConfig;
            common::authorization::AuthorizationConfig updateReportConfig, deleteReportConfig;

            // Get Reports
            getReportsConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::GET, getReportsConfig,
                std::bind(&ExpenseManagerReportsEndpoint::getReports, this, std::placeholders::_1)});

            // Get Report
            getReportConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::GET, getReportConfig,
                std::bind(&ExpenseManagerReportsEndpoint::getReport, this, std::placeholders::_1)});

            // Add Report
            addReportConfig.enabled = true;
            routes.push_back(Route{"/", RouteMethod::POST, addReportConfig,
                std::bind(&ExpenseManagerReportsEndpoint::addReport, this, std::placeholders::_1)});

            // Update Report
            updateReportConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::PATCH, updateReportConfig,
                std::bind(&ExpenseManagerReportsEndpoint::updateReport, this, std::placeholders::_1)});

            // Delete Report
            deleteReportConfig.enabled = true;
            routes.push_back(Route{"/:id", RouteMethod::DELETE, deleteReportConfig,
                std::bind(&ExpenseManagerReportsEndpoint::deleteReport, this, std::placeholders::_1)});
            logger_.info("ExpenseManagerReportsEndpoint::getRoutes Exit");

            for(auto route : routes){
                routes.push_back(Route{route.path, RouteMethod::OPTIONS, deleteReportConfig,
                    std::bind(&BaseEndpoint::handlePreflight, this, std::placeholders::_1)});
            }
            return routes;
        }
    }
}
