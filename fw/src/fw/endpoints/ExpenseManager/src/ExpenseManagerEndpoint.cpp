#include "ExpenseManagerEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        ExpenseManagerEndpoint::ExpenseManagerEndpoint()
        {
            logger_.info("ExpenseManagerEndpoint::ExpenseManagerEndpoint Entry");
            logger_.info("ExpenseManagerEndpoint::ExpenseManagerEndpoint Exit");
        }

        ExpenseManagerEndpoint::~ExpenseManagerEndpoint()
        {
            logger_.info("ExpenseManagerEndpoint::~ExpenseManagerEndpoint Entry");
            logger_.info("ExpenseManagerEndpoint::~ExpenseManagerEndpoint Exit");
        }

        void ExpenseManagerEndpoint::initialize()
        {
            logger_.info("ExpenseManagerEndpoint::initialize Entry");
            injections_ = new endpoints::ExpenseManager::ExpenseManagerEndpointInjections();
            // Accounts Sub-Router
            accountsEndpoint_ = std::make_shared<endpoints::ExpenseManager::ExpenseManagerAccountsEndpoint>(injections_);
            accountsEndpoint_->initialize();
            addSubRouter("accounts", accountsEndpoint_);
            // Categories Sub-Router
            categoriesEndpoint_ = std::make_shared<endpoints::ExpenseManager::ExpenseManagerCategoriesEndpoint>(injections_);
            categoriesEndpoint_->initialize();
            addSubRouter("categories", categoriesEndpoint_);
            // Transactions Sub-Router
            transactionEndpoint_ = std::make_shared<endpoints::ExpenseManager::ExpenseManagerTransactionsEndpoint>(injections_);
            transactionEndpoint_->initialize();
            addSubRouter("transactions", transactionEndpoint_);
            // Tags Sub-Router
            tagEndpoint_ = std::make_shared<endpoints::ExpenseManager::ExpenseManagerTagsEndpoint>(injections_);
            tagEndpoint_->initialize();
            addSubRouter("tags", tagEndpoint_);
            // Reports Sub-Router
            reportEndpoint_ = std::make_shared<endpoints::ExpenseManager::ExpenseManagerReportsEndpoint>(injections_);
            reportEndpoint_->initialize();
            addSubRouter("reports", reportEndpoint_);
            logger_.info("ExpenseManagerEndpoint::initialize Exit");
        }

        void *ExpenseManagerEndpoint::getInterface(ModuleUid uid)
        {
            logger_.info("ExpenseManagerEndpoint::getInterface Entry");
            void *interface = nullptr;
            if(uid == GET_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerEndpoint))
            {
                interface = this;
            }
            else if(uid == GET_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerAccountsEndpoint))
            {
                interface = accountsEndpoint_.get();
            }
            logger_.info("ExpenseManagerEndpoint::getInterface Exit");
            return interface;
        }

        void ExpenseManagerEndpoint::setInterface(ModuleUid uid, void *interface)
        {
            logger_.info("ExpenseManagerEndpoint::setInterface Entry");
            if(uid == GET_MODULE_UID(services::CommonService::IUtilityService))
            {
                injections_->utilityService = std::shared_ptr<services::CommonService::IUtilityService>(
                    static_cast<services::CommonService::IUtilityService *>(interface));
            }
            logger_.info("ExpenseManagerEndpoint::setInterface Exit");
        }

        void ExpenseManagerEndpoint::connect()
        {
            logger_.info("ExpenseManagerEndpoint::connect Entry");
            assert(injections_->utilityService != nullptr), "Utility Service is not set";
            logger_.info("ExpenseManagerEndpoint::connect Exit");
        }

        void *ExpenseManagerEndpoint::getInstance()
        {
            logger_.info("ExpenseManagerEndpoint::getInstance Entry");
            logger_.info("ExpenseManagerEndpoint::getInstance Exit");
            return this;
        }

        void ExpenseManagerEndpoint::shutdown()
        {
            logger_.info("ExpenseManagerEndpoint::shutdown Entry");
            accountsEndpoint_->shutdown();
            categoriesEndpoint_->shutdown();
            logger_.info("ExpenseManagerEndpoint::shutdown Exit");
        }
    }
}