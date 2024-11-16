#pragma once
#include <memory>
#include "IUtilityService.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class ExpenseManagerInjections
        {
        public:
            std::shared_ptr<services::CommonService::IUtilityService> utilityService;
        };
    }
}