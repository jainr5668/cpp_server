#ifndef MOCKIEXPENSEMANAGERTRANSACTIONSSERVICE_H
#define MOCKIEXPENSEMANAGERTRANSACTIONSSERVICE_H
#include "IExpenseManagerTransactionsService.h"
#include <gmock/gmock.h>

namespace services
{
    namespace ExpenseManagerService
    {
        class MockIExpenseManagerTransactionsService : public IExpenseManagerTransactionsService
        {
        };
    }
}
#endif // MOCKIEXPENSEMANAGERTRANSACTIONSSERVICE_H
