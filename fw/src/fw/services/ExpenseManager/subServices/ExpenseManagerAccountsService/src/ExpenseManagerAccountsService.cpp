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

        std::pair<bool, ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData> ExpenseManagerAccountsService::createAccount(
            ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsPostData expenseManagerAccountsPostData)
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
                expenseManagerAccountsDbData.accountType.value = ExpenseManagerAccountsServiceTypes::accountTypeToString.at(
                    expenseManagerAccountsPostData.accountType.value);
                expenseManagerAccountsDbData.currencyCode.value = ExpenseManagerAccountsServiceTypes::currencyCodeToString.at(
                    expenseManagerAccountsPostData.currencyCode.value);
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

        std::pair<bool, std::vector<ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData>> ExpenseManagerAccountsService::getAccounts(std::string userId)
        {
            logger.info("ExpenseManagerAccountsService::getAccounts Entry");
            auto dataResult = data_->retriveAccounts(userId);
            if (dataResult.first)
            {
                for (auto &account : dataResult.second)
                {
                    account.userId.reset();
                }
            }
            logger.info("ExpenseManagerAccountsService::getAccounts Exit");
            return dataResult;
        }

        std::pair<bool, ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData> ExpenseManagerAccountsService::getAccount(std::string userId, std::string accountId)
        {
            logger.info("ExpenseManagerAccountsService::getAccount Entry");
            auto dataResult = data_->retriveAccountById(userId, accountId);
            if (dataResult.first)
            {
                dataResult.second.userId.reset();
            }
            logger.info("ExpenseManagerAccountsService::getAccount Exit");
            return dataResult;
        }

        std::pair<bool, ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData> ExpenseManagerAccountsService::updateAccount(std::string userId, std::string accountId,
            ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsPatchData updateData)
        {
            logger.info("ExpenseManagerAccountsService::updateAccount Entry");
            ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData account;
            std::pair<bool, ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData> result;
            result.first = false;
            result.second = account;
            auto accountResult = getAccount(userId, accountId);
            if (accountResult.first)
            {
                account = accountResult.second;
                if (updateData.accountName.has_value())
                {
                    account.accountName.value = updateData.accountName.value();
                }
                if (updateData.description.has_value())
                {
                    account.description.value = updateData.description.value();
                }
                if (updateData.accountType.has_value())
                {
                    account.accountType.value = ExpenseManagerAccountsServiceTypes::accountTypeToString.at(updateData.accountType.value());
                }
                if (updateData.currencyCode.has_value())
                {
                    // TODO: When changing currency, convert the balance to the new currency if balance is not being updated
                    account.currencyCode.value = ExpenseManagerAccountsServiceTypes::currencyCodeToString.at(updateData.currencyCode.value());
                }
                if (updateData.balance.has_value())
                {
                    account.balance.value = std::to_string(updateData.balance.value());
                }
                if (updateData.isActive.has_value())
                {
                    account.isActive.value = updateData.isActive.value();
                }
                account.updatedAt.value = injections_->utilityService->timepoint_to_string(std::chrono::system_clock::now());
                result.first = data_->updateAccountById(account);
                if (!result.first)
                {
                    logger.error("ExpenseManagerAccountsService::updateAccount Account Update Failed");
                }
                else
                {
                    result.second = account;
                    result.second.userId.reset();
                }
            }
            else
            {
                result.first = false;
                logger.error("ExpenseManagerAccountsService::updateAccount Account Not Found");
            }
            logger.info("ExpenseManagerAccountsService::updateAccount Exit");
            return result;
        }

        bool ExpenseManagerAccountsService::removeAccount(std::string userId, std::string accountId)
        {
            logger.info("ExpenseManagerAccountsService::removeAccount Entry");
            auto account = getAccount(userId, accountId);
            bool result = false;
            if (account.first)
            {
                result = data_->deleteAccount(userId, accountId);
            }
            logger.info("ExpenseManagerAccountsService::removeAccount Exit");
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
            if (ExpenseManagerAccountsServiceTypes::currencyCodeToString.find(expenseManagerAccountsPostData.currencyCode.value) ==
                ExpenseManagerAccountsServiceTypes::currencyCodeToString.end())
            {
                result = false;
                logger.error("ExpenseManagerAccountsService::isPostDataValid Currency is not valid");
            }
            if (expenseManagerAccountsPostData.balance.value < 0)
            {
                result = false;
                logger.error("ExpenseManagerAccountsService::isPostDataValid Balance is not set");
            }
            logger.info("ExpenseManagerAccountsService::isPostDataValid Exit");
            return result;
        }
    }
}
