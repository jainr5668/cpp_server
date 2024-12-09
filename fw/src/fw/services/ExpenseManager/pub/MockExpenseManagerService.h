#ifndef MOCKEXPENSEMANAGERSERVICE_H
#define MOCKEXPENSEMANAGERSERVICE_H
#include "IExpenseManagerService.h"
#include <gmock/gmock.h>

namespace services
{
    namespace ExpenseManagerService
    {
        class MockExpenseManagerService : public IExpenseManagerService
        {
        };
    }
}
#endif // MOCKEXPENSEMANAGERSERVICE_H
