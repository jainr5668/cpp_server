#ifndef MOCKIEXPENSEMANAGERCATEGORIESSERVICE_H
#define MOCKIEXPENSEMANAGERCATEGORIESSERVICE_H
#include "IExpenseManagerCategoriesService.h"
#include <gmock/gmock.h>

namespace services
{
    namespace ExpenseManagerService
    {
        class MockIExpenseManagerCategoriesService : public IExpenseManagerCategoriesService
        {
        };
    }
}

#endif // MOCKIEXPENSEMANAGERCATEGORIESSERVICE_H