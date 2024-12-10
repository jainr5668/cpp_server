#ifndef EXPENSEMANAGERACCOUNTSSERVICE_H
#define EXPENSEMANAGERACCOUNTSSERVICE_H
#include "IExpenseManagerAccountsService.h"
#include "ExpenseManagerServiceInjections.h"
#include "ExpenseManagerAccountsServiceData.h"
#include "logger.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class ExpenseManagerAccountsService : public IExpenseManagerAccountsService
        {
        public:
            ExpenseManagerAccountsService(ExpenseManagerServiceInjections* injections);
            void initialize() override;
            void *getInterface(ModuleUid uid) override;
            void setInterface(ModuleUid uid, void *interface) override;
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID() override;
            ~ExpenseManagerAccountsService() = default;

            /***
             * @brief Create a new account
             * @param expenseManagerAccountsPostData The account data
             */
            std::pair<bool, ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsDbData> createAccount(ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsPostData expenseManagerAccountsPostData) override;

        private:
            Logger logger;
            ExpenseManagerServiceInjections *injections_;
            ExpenseManagerAccountsServiceData *data_;

            /**
             * @brief Check if the post data is valid
             */
            bool isPostDataValid(ExpenseManagerAccountsServiceTypes::ExpenseManagerAccountsPostData expenseManagerAccountsPostData);
        };
    }
}
#endif // EXPENSEMANAGERACCOUNTSSERVICE_H
