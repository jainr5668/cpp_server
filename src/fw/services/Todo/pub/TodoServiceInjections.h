#pragma once
#include "ITodoServiceData.h"
#include <memory>

namespace services
{
    namespace TodoService
    {
        class TodoServiceInjections
        {
        public:
            std::unique_ptr<services::TodoService::ITodoServiceData> todoServiceData{nullptr};
        };
    } // namespace services::TodoService
} // namespace services