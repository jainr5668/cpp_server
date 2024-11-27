#ifndef EXPENSEMANAGERINJECTIONS_H
#define EXPENSEMANAGERINJECTIONS_H
#include <memory>
#include "IUtilityService.h"
#include "IExpenseManagerAccountsService.h"
#include "IExpenseManagerCategoriesService.h"
#include "IExpenseManagerReportsService.h"
#include "IExpenseManagerTagsService.h"
#include "IExpenseManagerTransactionsService.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerEndpointInjections
        {
        public:
            std::shared_ptr<services::CommonService::IUtilityService> utilityService;
            std::shared_ptr<services::ExpenseManagerService::IExpenseManagerAccountsService> accountsService_{nullptr};
            std::shared_ptr<services::ExpenseManagerService::IExpenseManagerCategoriesService> categoriesService_{nullptr};
            std::shared_ptr<services::ExpenseManagerService::IExpenseManagerReportsService> reportsService_{nullptr};
            std::shared_ptr<services::ExpenseManagerService::IExpenseManagerTagsService> tagsService_{nullptr};
            std::shared_ptr<services::ExpenseManagerService::IExpenseManagerTransactionsService> transactionsService_{nullptr};
        };
    }
}
#endif // EXPENSEMANAGERINJECTIONS_H
