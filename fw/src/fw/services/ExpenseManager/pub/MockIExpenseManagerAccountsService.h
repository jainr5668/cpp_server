#ifndef MOCKIEXPENSEMANAGERACCOUNTSSERVICE_H
#define MOCKIEXPENSEMANAGERACCOUNTSSERVICE_H
#include "IExpenseManagerAccountsService.h"
#include <gmock/gmock.h>

namespace services
{
    namespace ExpenseManagerService
    {
        class MockIExpenseManagerAccountsService : public IExpenseManagerAccountsService
        {
        };
    }
}
#endif // MOCKIEXPENSEMANAGERACCOUNTSSERVICE_H