#pragma once
#include "UtilityService.h"
#include <memory>

namespace services{
    namespace CommonService{
        class CommonServiceInjections
        {
        public:
            std::shared_ptr<services::CommonService::UtilityService> utilityService{nullptr};
        };
    }
}