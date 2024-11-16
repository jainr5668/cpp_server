#pragma once
#include "IExpenseManagerEndpoint.h"
#include "ExpenseManagerInjections.h"
#include "ExpenseManagerAccountsEndpoint.h"
#include "ExpenseManagerCategoriesEndpoint.h"
#include "ExpenseManagerTransationsEndpoint.h"
#include "ExpenseManagerTagsEndpoint.h"
#include "ExpenseManagerReportsEndpoint.h"
#include "logger.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerEndpoint : public IExpenseManagerEndpoint
        {
        public:
            ExpenseManagerEndpoint();
            ~ExpenseManagerEndpoint();
            void connect();
            void *getInstance();
            void *getInterface(ModuleUid uid);
            void initialize();
            void setInterface(ModuleUid uid, void *interface);
            void shutdown();
        private:
            std::shared_ptr<endpoints::ExpenseManager::ExpenseManagerAccountsEndpoint> accountsEndpoint_;
            std::shared_ptr<endpoints::ExpenseManager::ExpenseManagerCategoriesEndpoint> categoriesEndpoint_;
            std::shared_ptr<endpoints::ExpenseManager::ExpenseManagerTransationsEndpoint> transactionEndpoint_;
            std::shared_ptr<endpoints::ExpenseManager::ExpenseManagerTagsEndpoint> tagEndpoint_;
            std::shared_ptr<endpoints::ExpenseManager::ExpenseManagerReportsEndpoint> reportEndpoint_;
            endpoints::ExpenseManager::ExpenseManagerInjections* injections_;
            Logger logger_;
        };
    }
}