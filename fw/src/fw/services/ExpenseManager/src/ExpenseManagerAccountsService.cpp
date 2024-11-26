#include "ExpenseManagerAccountsService.h"

namespace services
{
    namespace ExpenseManagerService
    {
        ExpenseManagerAccountsService::ExpenseManagerAccountsService(ExpenseManagerServiceInjections* injections)
        {
            logger.info("ExpenseManagerAccountsService::ExpenseManagerAccountsService Entry");
            injections_ = injections;
            logger.info("ExpenseManagerAccountsService::ExpenseManagerAccountsService Exit");
        }

        void ExpenseManagerAccountsService::initialize()
        {
            logger.info("ExpenseManagerAccountsService::initialize Entry");
            logger.info("ExpenseManagerAccountsService::initialize Exit");
        }

        void *ExpenseManagerAccountsService::getInterface(ModuleUid uid)
        {
            logger.info("ExpenseManagerAccountsService::getInterface Entry");
            void *interface = nullptr;
            if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerAccountsService))
            {
                interface = this;
            }
            logger.info("ExpenseManagerAccountsService::getInterface Exit");
            return interface;
        }

        void ExpenseManagerAccountsService::setInterface(ModuleUid uid, void *interface)
        {
            logger.info("ExpenseManagerAccountsService::setInterface Entry");
            logger.info("ExpenseManagerAccountsService::setInterface Exit");
        }

        void ExpenseManagerAccountsService::connect()
        {
            logger.info("ExpenseManagerAccountsService::connect Entry");
            assert(injections_->utilityService != nullptr), "Utility Service is not set";
            logger.info("ExpenseManagerAccountsService::connect Exit");
        }

        void *ExpenseManagerAccountsService::getInstance()
        {
            logger.info("ExpenseManagerAccountsService::getInstance Entry");
            logger.info("ExpenseManagerAccountsService::getInstance Exit");
            return nullptr;
        }

        void ExpenseManagerAccountsService::shutdown()
        {
            logger.info("ExpenseManagerAccountsService::shutdown Entry");
            logger.info("ExpenseManagerAccountsService::shutdown Exit");
        }

        ModuleUid ExpenseManagerAccountsService::getInterfaceUID()
        {
            return GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerAccountsService);
        }
    }
}