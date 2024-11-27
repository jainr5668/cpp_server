#include "ExpenseManagerReportsService.h"

namespace services
{
    namespace ExpenseManagerService
    {
        ExpenseManagerReportsService::ExpenseManagerReportsService(ExpenseManagerServiceInjections* injections)
            : injections_(injections)
        {
            logger.info("ExpenseManagerReportsService::ExpenseManagerReportsService Entry");
            logger.info("ExpenseManagerReportsService::ExpenseManagerReportsService Exit");
        }

        void ExpenseManagerReportsService::initialize()
        {
            logger.info("ExpenseManagerReportsService::initialize Entry");
            logger.info("ExpenseManagerReportsService::initialize Exit");
        }

        void *ExpenseManagerReportsService::getInterface(ModuleUid uid)
        {
            logger.info("ExpenseManagerReportsService::getInterface Entry");
            void *interface = nullptr;
            if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerReportsService))
            {
                interface = this;
            }
            logger.info("ExpenseManagerReportsService::getInterface Exit");
            return interface;
        }

        void ExpenseManagerReportsService::setInterface(ModuleUid uid, void *interface)
        {
            logger.info("ExpenseManagerReportsService::setInterface Entry");
            logger.info("ExpenseManagerReportsService::setInterface Exit");
        }

        void ExpenseManagerReportsService::connect()
        {
            logger.info("ExpenseManagerReportsService::connect Entry");
            assert(injections_->utilityService != nullptr), "Utility Service is not set";
            logger.info("ExpenseManagerReportsService::connect Exit");
        }

        void *ExpenseManagerReportsService::getInstance()
        {
            logger.info("ExpenseManagerReportsService::getInstance Entry");
            logger.info("ExpenseManagerReportsService::getInstance Exit");
            return this;
        }

        void ExpenseManagerReportsService::shutdown()
        {
            logger.info("ExpenseManagerReportsService::shutdown Entry");
            logger.info("ExpenseManagerReportsService::shutdown Exit");
        }

        ModuleUid ExpenseManagerReportsService::getInterfaceUID()
        {
            return GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerReportsService);
        }
    }
}
