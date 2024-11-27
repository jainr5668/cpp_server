#ifndef COMMONSERVICEINJECTIONS_H
#define COMMONSERVICEINJECTIONS_H
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
#endif // COMMONSERVICEINJECTIONS_H
