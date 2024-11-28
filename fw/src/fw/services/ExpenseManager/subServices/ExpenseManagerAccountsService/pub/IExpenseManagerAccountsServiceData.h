#ifndef IEXPENSEMANAGERACCOUNTSSERVICEDATA_H
#define IEXPENSEMANAGERACCOUNTSSERVICEDATA_H
#include <string>
#include <vector>
#include "ExpenseManagerAccountsServiceTypes.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class IExpenseManagerAccountsServiceData
        {
        public:
            /**
             * @brief Destroy the IExpenseManagerAccountsServiceData object
             */
            virtual ~IExpenseManagerAccountsServiceData() = default;

            /**
             * @brief This function is used to retrive all the accounts
             * @param userId The user id of the user
             */
            virtual std::pair<bool, std::vector<services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData>> retriveAccounts(std::string) = 0;

            /**
             * @brief This function is used to retrive the account by id
             * @param userId The user id of the user
             * @param accountId The account id of the account
             */
            virtual std::pair<bool, services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData> retriveAccountById(std::string, std::string) = 0;

            /**
             * @brief This function is used to insert the account
             * @param data The data of the account
             */
            virtual bool insertAccount(services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData) = 0;

            /**
             * @brief This function is used to delete the account
             * @param userId The user id of the user
             * @param accountId The account id of the account
             */
            virtual bool deleteAccount(std::string, std::string) = 0;

            /**
             * @brief This function is used to update the account by id
             * @param account The data of the account
             */
            virtual bool updateAccountById(services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData) = 0;
        };
    } // namespace services::ExpenseManagerService
} // namespace services
#endif // IEXPENSEMANAGERACCOUNTSSERVICEDATA_H