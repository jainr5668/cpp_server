#ifndef TODOENDPOINTINJECTIONS_H
#define TODOENDPOINTINJECTIONS_H

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
#endif // TODOENDPOINTINJECTIONS_H
