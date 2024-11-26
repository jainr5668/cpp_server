#ifndef EXPENSEMANAGERINJECTIONS_H
#define EXPENSEMANAGERINJECTIONS_H
#include <memory>
#include "IUtilityService.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerEndpointInjections
        {
        public:
            std::shared_ptr<services::CommonService::IUtilityService> utilityService;
        };
    }
}
#endif // EXPENSEMANAGERINJECTIONS_H