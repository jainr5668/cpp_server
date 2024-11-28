#ifndef EXPENSEMANAGERACCOUNTSSERVICEDATA_H
#define EXPENSEMANAGERACCOUNTSSERVICEDATA_H

#include "IExpenseManagerAccountsServiceData.h"
#include "Data.h"
#include <memory>
#include "logger.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class ExpenseManagerAccountsServiceData : public IExpenseManagerAccountsServiceData
        {
        public:
            ExpenseManagerAccountsServiceData(std::shared_ptr<Data>);
            ~ExpenseManagerAccountsServiceData() = default;

            /**
             * @brief This function is used to retrive all the accounts
             * @param userId The user id of the user
             */
            std::pair<bool, std::vector<services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData>> \
                retriveAccounts(std::string) override;

            /**
             * @brief This function is used to retrive the account by id
             * @param userId The user id of the user
             */
            std::pair<bool, services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData> \
                retriveAccountById(std::string, std::string) override;

            /**
             * @brief This function is used to insert the account
             * @param data The data of the account
             */
            bool insertAccount(services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData) override;

            /**
             * @brief This function is used to delete the account
             * @param userId The user id of the user
             * @param accountId The account id of the account
             */
            bool deleteAccount(std::string, std::string) override;

            /**
             * @brief This function is used to update the account by id
             * @param account The data of the account
             */
            bool updateAccountById(services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData) override;
        private:
            Logger logger;
            std::shared_ptr<Data> data_;
        };
    }
}

#endif // EXPENSEMANAGERACCOUNTSSERVICEDATA_H