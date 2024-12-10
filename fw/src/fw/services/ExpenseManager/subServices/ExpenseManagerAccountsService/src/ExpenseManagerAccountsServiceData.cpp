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
            std::vector<std::string> queries = {
                "CREATE TABLE IF NOT EXISTS accounts (id TEXT, userId TEXT NOT NULL, accountName TEXT NOT NULL, description TEXT NOT NULL, accountType " 
                "VARCHAR(100) NOT NULL, currencyCode VARCHAR(50) NOT NULL, balance TEXT NOT NULL, updatedAt TEXT NOT NULL, isActive VARCHAR(10) NOT NULL, "
                "createdAt TEXT NOT NULL);"
            };
            for (auto &query : queries)
            {
                data_->execute(query);
            }
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

        std::pair<bool, ExpenseManagerAccountsDbData> ExpenseManagerAccountsServiceData::retriveAccountById(std::string userId, std::string accountId)
        {
            logger.info("ExpenseManagerAccountsServiceData::retriveAccountById Entry");
            ExpenseManagerAccountsDbData account;
            std::pair<bool, ExpenseManagerAccountsDbData> result;
            result.first = false;
            result.second = account;
            logger.info("ExpenseManagerAccountsServiceData::retriveAccountById Exit");
            return result;
        }

        bool ExpenseManagerAccountsServiceData::insertAccount(ExpenseManagerAccountsDbData account)
        {
            logger.info("ExpenseManagerAccountsServiceData::insertAccount Entry");
            auto query = data_->createInsertQuery("accounts", account);
            bool result = false;
            if (!query.empty())
            {
                auto insertReturn = data_->execute(query);
                result = true;
                
            }
            logger.info("ExpenseManagerAccountsServiceData::insertAccount Exit");
            return result;
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