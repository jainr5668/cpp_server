#include "ExpenseManagerCategoriesService.h"

namespace services
{
    namespace ExpenseManagerService
    {
        ExpenseManagerCategoriesService::ExpenseManagerCategoriesService(ExpenseManagerServiceInjections* injections)
        {
            logger.info("ExpenseManagerCategoriesService::ExpenseManagerCategoriesService Entry");
            injections_ = injections;
            logger.info("ExpenseManagerCategoriesService::ExpenseManagerCategoriesService Exit");
        }

        void ExpenseManagerCategoriesService::initialize()
        {
            logger.info("ExpenseManagerCategoriesService::initialize Entry");
            logger.info("ExpenseManagerCategoriesService::initialize Exit");
        }

        void *ExpenseManagerCategoriesService::getInterface(ModuleUid uid)
        {
            logger.info("ExpenseManagerCategoriesService::getInterface Entry");
            void *interface = nullptr;
            if (uid == GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerCategoriesService))
            {
                interface = this;
            }
            logger.info("ExpenseManagerCategoriesService::getInterface Exit");
            return interface;
        }

        void ExpenseManagerCategoriesService::setInterface(ModuleUid uid, void *interface)
        {
            logger.info("ExpenseManagerCategoriesService::setInterface Entry");
            logger.info("ExpenseManagerCategoriesService::setInterface Exit");
        }

        void ExpenseManagerCategoriesService::connect()
        {
            logger.info("ExpenseManagerCategoriesService::connect Entry");
            assert(injections_->utilityService != nullptr), "Utility Service is not set";
            logger.info("ExpenseManagerCategoriesService::connect Exit");
        }

        void *ExpenseManagerCategoriesService::getInstance()
        {
            logger.info("ExpenseManagerCategoriesService::getInstance Entry");
            logger.info("ExpenseManagerCategoriesService::getInstance Exit");
            return nullptr;
        }

        void ExpenseManagerCategoriesService::shutdown()
        {
            logger.info("ExpenseManagerCategoriesService::shutdown Entry");
            logger.info("ExpenseManagerCategoriesService::shutdown Exit");
        }

        ModuleUid ExpenseManagerCategoriesService::getInterfaceUID()
        {
            return GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerCategoriesService);
        }
    }
}