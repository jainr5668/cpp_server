#ifndef TODOSERVICEINJECTIONS_H
#define TODOSERVICEINJECTIONS_H
#include "ITodoServiceData.h"
#include <memory>
#include "IUtilityService.h"

namespace services
{
    namespace TodoService
    {
        class TodoServiceInjections
        {
        public:
            std::unique_ptr<services::TodoService::ITodoServiceData> todoServiceData{nullptr};
            std::shared_ptr<services::CommonService::IUtilityService> utilityService{nullptr};
        };
    } // namespace services::TodoService
} // namespace services
#endif // TODOSERVICEINJECTIONS_H
