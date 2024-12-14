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
            result.first = true;
            result.second = accounts;
            std::string query = "SELECT * FROM accounts WHERE userId = '" + userId + "'";
            auto data = data_->execute(query);
            if (data.size() > 0)
            {
                for (auto &row : data)
                {
                    
                    result.second.push_back(ExpenseManagerAccountsDbData{row});
                }
            }
            logger.info("ExpenseManagerAccountsServiceData::retriveAccounts Exit");
            return result;
        }

        std::pair<bool, ExpenseManagerAccountsDbData> ExpenseManagerAccountsServiceData::retriveAccountById(std::string userId, std::string accountId)
        {
            logger.info("ExpenseManagerAccountsServiceData::retriveAccountById Entry");
            std::pair<bool, ExpenseManagerAccountsDbData> result{false, ExpenseManagerAccountsDbData{}};
            std::string query = "SELECT * FROM accounts WHERE userId = '" + userId + "' AND id = '" + accountId + "'";
            auto data = data_->execute(query);
            if (data.size() == 1)
            {
                result.first = true;
                for (auto &row : data)
                {
                    result.second = ExpenseManagerAccountsDbData{row};
                }
            }
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
            bool result = false;
            std::string query = "DELETE FROM accounts WHERE userId = '" + userId + "' AND id = '" + accountId + "'";
            data_->execute(query);
            result = true;
            logger.info("ExpenseManagerAccountsServiceData::deleteAccount Exit");
            return result;
        }

        bool ExpenseManagerAccountsServiceData::updateAccountById(ExpenseManagerAccountsDbData account)
        {
            logger.info("ExpenseManagerAccountsServiceData::updateAccountById Entry");
            bool result = false;
            std::string query = "UPDATE accounts SET accountName = '" + account.accountName.value + "', description = '" + account.description.value + "', accountType = '" 
                + account.accountType.value + "', currencyCode = '" + account.currencyCode.value + "', balance = '" + account.balance.value + "', updatedAt = '" + 
                account.updatedAt.value + "', isActive = '" + account.isActive.value + "' WHERE id = '" + account.id.value + "'";
            data_->execute(query);
            result = true;
            logger.info("ExpenseManagerAccountsServiceData::updateAccountById Exit");
            return result;
        }
    }
}