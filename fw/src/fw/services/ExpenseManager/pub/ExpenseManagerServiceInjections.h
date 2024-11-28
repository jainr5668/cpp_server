#ifndef EXPENSEMANAGERSERVICEINJECTIONS_H
#define EXPENSEMANAGERSERVICEINJECTIONS_H

#include <memory>
#include "IUtilityService.h"
#include "Data.h"
#include "IExpenseManagerAccountsService.h"
#include "IExpenseManagerCategoriesService.h"
#include "IExpenseManagerReportsService.h"
#include "IExpenseManagerTagsService.h"
#include "IExpenseManagerTransactionsService.h"

namespace services
{
    namespace ExpenseManagerService
    {
        class ExpenseManagerServiceInjections
        {
        public:
            std::shared_ptr<services::CommonService::IUtilityService> utilityService{nullptr};
            std::shared_ptr<Data> data{nullptr};
            std::shared_ptr<services::ExpenseManagerService::IExpenseManagerAccountsService> accountsService_{nullptr};
            std::shared_ptr<services::ExpenseManagerService::IExpenseManagerCategoriesService> categoriesService_{nullptr};
            std::shared_ptr<services::ExpenseManagerService::IExpenseManagerReportsService> reportsService_{nullptr};
            std::shared_ptr<services::ExpenseManagerService::IExpenseManagerTagsService> tagsService_{nullptr};
            std::shared_ptr<services::ExpenseManagerService::IExpenseManagerTransactionsService> transactionsService_{nullptr};
        };
    }
}
#endif // EXPENSEMANAGERSERVICEINJECTIONS_H
