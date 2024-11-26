#ifndef MOCKIEXPENSEMANAGERREPORTSSERVICE_H
#define MOCKIEXPENSEMANAGERREPORTSSERVICE_H
#include "IExpenseManagerReportsService.h"
#include <gmock/gmock.h>

namespace services
{
    namespace ExpenseManagerService
    {
        class MockIExpenseManagerReportsService : public IExpenseManagerReportsService
        {
        };
    }
}
#endif // MOCKIEXPENSEMANAGERREPORTSSERVICE_H