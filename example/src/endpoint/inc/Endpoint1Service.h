#pragma once

#include "IEndpoint1Service.h"

#include "Endpoint1Types.h"

namespace Example
{
    namespace Endpoint
    {
        class Endpoint1Service : public IEndpoint1Service
        {
        public:
            Endpoint1Service() = default;
            ~Endpoint1Service() override = default;

            std::pair<bool, Example::Endpoint::Endpoint1Response> processRequest1(Example::Endpoint::Endpoint1Request &request) override;
        };
    } // namespace Endpoint
} // namespace Example