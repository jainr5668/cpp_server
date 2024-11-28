#ifndef MOCKIEXPENSEMANAGERACCOUNTSSERVICEDATA_H
#define MOCKIEXPENSEMANAGERACCOUNTSSERVICEDATA_H
#include "IExpenseManagerAccountsServiceData.h"
#include "gmock/gmock.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class MockIExpenseManagerAccountsServiceData : public IExpenseManagerAccountsServiceData
        {
        public:
            MOCK_METHOD1(retriveAccounts, std::pair<bool, std::vector<services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData>>(std::string));
            MOCK_METHOD2(retriveAccountById, std::pair<bool, services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData>(std::string, std::string));
            MOCK_METHOD1(insertAccount, bool(services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData));
            MOCK_METHOD2(deleteAccount, bool(std::string, std::string));
            MOCK_METHOD1(updateAccountById, bool(services::ExpenseManagerService::ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData));
        };
    } // namespace services::ExpenseManagerService
} // namespace services
#endif