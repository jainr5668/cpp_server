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
            virtual ~IExpenseManagerAccountsServiceData() = default;
            virtual std::pair<bool, std::vector<services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData>> retriveAccounts(std::string) = 0;
            virtual bool insertAccount(services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData) = 0;
            virtual bool deleteAccount(std::string, std::string) = 0;
            virtual bool updateAccountById(services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData) = 0;
        };
    } // namespace services::ExpenseManagerService
} // namespace services
#endif // IEXPENSEMANAGERACCOUNTSSERVICEDATA_H