#include "ExpenseManagerAccountsServiceData.h"

using ExpenseManagerAccountsDbData = services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData;

namespace services
{
    namespace ExpenseManagerService
    {
        ExpenseManagerAccountsServiceData::ExpenseManagerAccountsServiceData(std::shared_ptr<Data> data)
        {
            logger.info("ExpenseManagerAccountsServiceData::ExpenseManagerAccountsServiceData Entry");
            data_ = data;
            logger.info("ExpenseManagerAccountsServiceData::ExpenseManagerAccountsServiceData Exit");
        }

        std::pair<bool, std::vector<ExpenseManagerAccountsDbData>> ExpenseManagerAccountsServiceData::retriveAccounts(std::string userId)
        {
            logger.info("ExpenseManagerAccountsServiceData::retriveAccounts Entry");
            std::vector<ExpenseManagerAccountsDbData> accounts;
            std::pair<bool, std::vector<ExpenseManagerAccountsDbData>> result;
            result.first = false;
            result.second = accounts;
            logger.info("ExpenseManagerAccountsServiceData::retriveAccounts Exit");
            return result;
        }

        bool ExpenseManagerAccountsServiceData::insertAccount(ExpenseManagerAccountsDbData account)
        {
            logger.info("ExpenseManagerAccountsServiceData::insertAccount Entry");
            logger.info("ExpenseManagerAccountsServiceData::insertAccount Exit");
            return false;
        }

        bool ExpenseManagerAccountsServiceData::deleteAccount(std::string userId, std::string accountId)
        {
            logger.info("ExpenseManagerAccountsServiceData::deleteAccount Entry");
            logger.info("ExpenseManagerAccountsServiceData::deleteAccount Exit");
            return false;
        }

        bool ExpenseManagerAccountsServiceData::updateAccountById(ExpenseManagerAccountsDbData account)
        {
            logger.info("ExpenseManagerAccountsServiceData::updateAccountById Entry");
            logger.info("ExpenseManagerAccountsServiceData::updateAccountById Exit");
            return false;
        }
    }
}