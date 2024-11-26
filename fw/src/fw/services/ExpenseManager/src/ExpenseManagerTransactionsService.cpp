#include "ExpenseManagerTransactionsService.h"

namespace services
{
    namespace ExpenseManagerService
    {
        ExpenseManagerTransactionsService::ExpenseManagerTransactionsService(ExpenseManagerServiceInjections* injections)
            : injections_(injections)
        {
            logger.info("ExpenseManagerTransactionsService::ExpenseManagerTransactionsService Entry");
            logger.info("ExpenseManagerTransactionsService::ExpenseManagerTransactionsService Exit");
        }

        void ExpenseManagerTransactionsService::initialize()
        {
            logger.info("ExpenseManagerTransactionsService::initialize Entry");
            logger.info("ExpenseManagerTransactionsService::initialize Exit");
        }

        void *ExpenseManagerTransactionsService::getInterface(ModuleUid uid)
        {
            logger.info("ExpenseManagerTransactionsService::getInterface Entry");
            void *interface = nullptr;
            if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerTransactionsService))
            {
                interface = this;
            }
            logger.info("ExpenseManagerTransactionsService::getInterface Exit");
            return interface;
        }

        void ExpenseManagerTransactionsService::setInterface(ModuleUid uid, void *interface)
        {
            logger.info("ExpenseManagerTransactionsService::setInterface Entry");
            logger.info("ExpenseManagerTransactionsService::setInterface Exit");
        }

        void ExpenseManagerTransactionsService::connect()
        {
            logger.info("ExpenseManagerTransactionsService::connect Entry");
            assert(injections_->utilityService != nullptr), "Utility Service is not set";
            logger.info("ExpenseManagerTransactionsService::connect Exit");
        }

        void *ExpenseManagerTransactionsService::getInstance()
        {
            logger.info("ExpenseManagerTransactionsService::getInstance Entry");
            logger.info("ExpenseManagerTransactionsService::getInstance Exit");
            return this;
        }

        void ExpenseManagerTransactionsService::shutdown()
        {
            logger.info("ExpenseManagerTransactionsService::shutdown Entry");
            logger.info("ExpenseManagerTransactionsService::shutdown Exit");
        }

        ModuleUid ExpenseManagerTransactionsService::getInterfaceUID()
        {
            return GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerTransactionsService);
        }
    }
}