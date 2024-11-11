#pragma once

#include "ITodoService.h"
#include <memory>

namespace endpoints
{
    namespace TodoEndpoint
    {
        class TodoEndpointInjections
        {
        public:
            std::shared_ptr<services::TodoService::ITodoService> todoService{nullptr};
        };
    } // namespace TodoEndpoint
} // namespace endpoints