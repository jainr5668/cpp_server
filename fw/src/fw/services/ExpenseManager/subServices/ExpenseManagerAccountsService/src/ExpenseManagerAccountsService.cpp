#include "ExpenseManagerAccountsService.h"
#include <chrono>

namespace services
{
    namespace ExpenseManagerService
    {
        ExpenseManagerAccountsService::ExpenseManagerAccountsService(ExpenseManagerServiceInjections *injections)
        {
            logger.info("ExpenseManagerAccountsService::ExpenseManagerAccountsService Entry");
            injections_ = injections;
            logger.info("ExpenseManagerAccountsService::ExpenseManagerAccountsService Exit");
        }

        void ExpenseManagerAccountsService::initialize()
        {
            logger.info("ExpenseManagerAccountsService::initialize Entry");
            data_ = new ExpenseManagerAccountsServiceData(injections_->data);
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
            assert(injections_->data != nullptr), "Data is not set";
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
            logger.info("ExpenseManagerAccountsService::getInterfaceUID Entry");
            logger.info("ExpenseManagerAccountsService::getInterfaceUID Exit");
            return GET_MODULE_UID(services::ExpenseManagerService::IExpenseManagerAccountsService);
        }

        std::pair<bool, ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData> ExpenseManagerAccountsService::createAccount(ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsPostData expenseManagerAccountsPostData)
        {
            logger.info("ExpenseManagerAccountsService::createAccount Entry");
            std::pair<bool, ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData> result{
                false, ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData{}};
            auto validationResult = isPostDataValid(expenseManagerAccountsPostData);
            if (validationResult)
            {
                ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData expenseManagerAccountsDbData;
                expenseManagerAccountsDbData.id.value = injections_->utilityService->get_uuid();
                expenseManagerAccountsDbData.userId = expenseManagerAccountsPostData.userId.value;
                expenseManagerAccountsDbData.accountName = expenseManagerAccountsPostData.accountName;
                expenseManagerAccountsDbData.accountType.value = expenseManagerAccountsPostData.accountTypeToString();
                expenseManagerAccountsDbData.currencyCode = expenseManagerAccountsPostData.currencyCode;
                expenseManagerAccountsDbData.balance.value = std::to_string(expenseManagerAccountsPostData.balance.value);
                expenseManagerAccountsDbData.isActive.value = "true";
                expenseManagerAccountsDbData.createdAt.value = injections_->utilityService->timepoint_to_string(std::chrono::system_clock::now());
                expenseManagerAccountsDbData.updatedAt = expenseManagerAccountsDbData.createdAt;
                expenseManagerAccountsDbData.description = expenseManagerAccountsPostData.description;
                result.first = data_->insertAccount(expenseManagerAccountsDbData);
                if (result.first)
                {
                    result.second = expenseManagerAccountsDbData;
                    result.second.userId.reset();
                }
                else
                {
                    logger.error("ExpenseManagerAccountsService::createAccount Account Creation Failed");
                }
            }

            logger.info("ExpenseManagerAccountsService::createAccount Exit");
            return result;
        }

        bool ExpenseManagerAccountsService::isPostDataValid(ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsPostData expenseManagerAccountsPostData)
        {
            logger.info("ExpenseManagerAccountsService::isPostDataValid Entry");
            bool result = true;
            if (!expenseManagerAccountsPostData.accountName.has_value())
            {
                result = false;
                logger.error("ExpenseManagerAccountsService::isPostDataValid Name is not set");
            }
            if (!expenseManagerAccountsPostData.userId.has_value())
            {
                result = false;
                logger.error("ExpenseManagerAccountsService::isPostDataValid UserId is not set");
            }
            if (!expenseManagerAccountsPostData.accountType.has_value())
            {
                result = false;
                logger.error("ExpenseManagerAccountsService::isPostDataValid Account Type is not set");
            }
            if (!expenseManagerAccountsPostData.currencyCode.has_value())
            {
                result = false;
                logger.error("ExpenseManagerAccountsService::isPostDataValid Currency is not set");
            }
            if (!expenseManagerAccountsPostData.balance.has_value())
            {
                result = false;
                logger.error("ExpenseManagerAccountsService::isPostDataValid Balance is not set");
            }
            logger.info("ExpenseManagerAccountsService::isPostDataValid Exit");
            return result;
        }
    }
}
