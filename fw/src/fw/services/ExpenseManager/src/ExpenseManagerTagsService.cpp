#include "ExpenseManagerTagsService.h"

namespace services
{
    namespace ExpenseManagerService
    {
        ExpenseManagerTagsService::ExpenseManagerTagsService(ExpenseManagerServiceInjections* injections)
            : injections_(injections)
        {
            logger.info("ExpenseManagerTagsService::ExpenseManagerTagsService Entry");
            logger.info("ExpenseManagerTagsService::ExpenseManagerTagsService Exit");
        }

        void ExpenseManagerTagsService::initialize()
        {
            logger.info("ExpenseManagerTagsService::initialize Entry");
            logger.info("ExpenseManagerTagsService::initialize Exit");
        }

        void *ExpenseManagerTagsService::getInterface(ModuleUid uid)
        {
            logger.info("ExpenseManagerTagsService::getInterface Entry");
            void *interface = nullptr;
            if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerTagsService))
            {
                interface = this;
            }
            logger.info("ExpenseManagerTagsService::getInterface Exit");
            return interface;
        }

        void ExpenseManagerTagsService::setInterface(ModuleUid uid, void *interface)
        {
            logger.info("ExpenseManagerTagsService::setInterface Entry");
            logger.info("ExpenseManagerTagsService::setInterface Exit");
        }

        void ExpenseManagerTagsService::connect()
        {
            logger.info("ExpenseManagerTagsService::connect Entry");
            assert(injections_->utilityService != nullptr), "Utility Service is not set";
            logger.info("ExpenseManagerTagsService::connect Exit");
        }

        void *ExpenseManagerTagsService::getInstance()
        {
            logger.info("ExpenseManagerTagsService::getInstance Entry");
            logger.info("ExpenseManagerTagsService::getInstance Exit");
            return this;
        }

        void ExpenseManagerTagsService::shutdown()
        {
            logger.info("ExpenseManagerTagsService::shutdown Entry");
            logger.info("ExpenseManagerTagsService::shutdown Exit");
        }

        ModuleUid ExpenseManagerTagsService::getInterfaceUID()
        {
            return GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerTagsService);
        }
    }
}