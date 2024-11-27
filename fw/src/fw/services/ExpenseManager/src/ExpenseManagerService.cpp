#include "ExpenseManagerService.h"
#include "ExpenseManagerAccountsService.h"
#include "ExpenseManagerCategoriesService.h"
#include "ExpenseManagerReportsService.h"
#include "ExpenseManagerTagsService.h"
#include "ExpenseManagerTransactionsService.h"

namespace services
{
    namespace ExpenseManagerService
    {
        ExpenseManagerService::ExpenseManagerService()
        {
            logger.info("ExpenseManagerService::ExpenseManagerService Entry");
            logger.info("ExpenseManagerService::ExpenseManagerService Exit");
        }

        void ExpenseManagerService::initialize()
        {
            logger.info("ExpenseManagerService::initialize Entry");
            injections_ = new ExpenseManagerServiceInjections();
            injections_->accountsService_ = std::make_shared<services::ExpenseManagerService::ExpenseManagerAccountsService>(injections_);
            injections_->categoriesService_ = std::make_shared<services::ExpenseManagerService::ExpenseManagerCategoriesService>(injections_);
            injections_->reportsService_ = std::make_shared<services::ExpenseManagerService::ExpenseManagerReportsService>(injections_);
            injections_->tagsService_ = std::make_shared<services::ExpenseManagerService::ExpenseManagerTagsService>(injections_);
            injections_->transactionsService_ = std::make_shared<services::ExpenseManagerService::ExpenseManagerTransactionsService>(injections_);
            logger.info("ExpenseManagerService::initialize Exit");
        }

        void *ExpenseManagerService::getInterface(ModuleUid uid)
        {
            logger.info("ExpenseManagerService::getInterface Entry");
            void *interface = nullptr;
            if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerService))
            {
                interface = this;
            }
            else if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerAccountsService))
            {
                interface = injections_->accountsService_.get();
            }
            else if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerCategoriesService))
            {
                interface = injections_->categoriesService_.get();
            }
            else if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerReportsService))
            {
                interface = injections_->reportsService_.get();
            }
            else if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerTagsService))
            {
                interface = injections_->tagsService_.get();
            }
            else if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerTransactionsService))
            {
                interface = injections_->transactionsService_.get();
            }
            logger.info("ExpenseManagerService::getInterface Exit");
            return interface;
        }

        void ExpenseManagerService::setInterface(ModuleUid uid, void *interface)
        {
            logger.info("ExpenseManagerService::setInterface Entry");
            if (uid == GET_MODULE_UID(services::CommonService::IUtilityService))
            {
                injections_->utilityService = std::shared_ptr<services::CommonService::IUtilityService>(
                    static_cast<services::CommonService::IUtilityService *>(interface));
            }
            logger.info("ExpenseManagerService::setInterface Exit");
        }

        void ExpenseManagerService::connect()
        {
            logger.info("ExpenseManagerService::connect Entry");
            assert(injections_->utilityService != nullptr), "Utility Service is not set";
            injections_->accountsService_->connect();
            injections_->categoriesService_->connect();
            injections_->reportsService_->connect();
            injections_->tagsService_->connect();
            injections_->transactionsService_->connect();
            logger.info("ExpenseManagerService::connect Exit");
        }

        void *ExpenseManagerService::getInstance()
        {
            logger.info("ExpenseManagerService::getInstance Entry");
            logger.info("ExpenseManagerService::getInstance Exit");
            return nullptr;
        }

        void ExpenseManagerService::shutdown()
        {
            logger.info("ExpenseManagerService::shutdown Entry");
            injections_->categoriesService_->shutdown();
            injections_->accountsService_->shutdown();
            injections_->reportsService_->shutdown();
            injections_->tagsService_->shutdown();
            injections_->transactionsService_->shutdown();
            logger.info("ExpenseManagerService::shutdown Exit");
        }

        ExpenseManagerService::~ExpenseManagerService()
        {
            logger.info("ExpenseManagerService::~ExpenseManagerService Entry");
            logger.info("ExpenseManagerService::~ExpenseManagerService Exit");
        }

        ModuleUid ExpenseManagerService::getInterfaceUID()
        {
            logger.info("ExpenseManagerService::getInterfaceUID Entry");
            logger.info("ExpenseManagerService::getInterfaceUID Exit");
            return GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerService);
        }
    }
}
