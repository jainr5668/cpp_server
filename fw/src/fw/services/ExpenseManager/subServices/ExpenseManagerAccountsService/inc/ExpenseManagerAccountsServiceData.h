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

            std::pair<bool, std::vector<services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData>> retriveAccounts(std::string) override;
            bool insertAccount(services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData) override;
            bool deleteAccount(std::string, std::string) override;
            bool updateAccountById(services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData) override;
        private:
            Logger logger;
            std::shared_ptr<Data> data_;
        };
    }
}

#endif // EXPENSEMANAGERACCOUNTSSERVICEDATA_H