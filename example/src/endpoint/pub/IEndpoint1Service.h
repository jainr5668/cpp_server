#pragma once
#include <iostream>
#include <string>
#include "Endpoint1Types.h"


namespace Example
{
    namespace Endpoint
    {
        class IEndpoint1Service
        {
        public:
            virtual ~IEndpoint1Service() = default;
            virtual std::pair<bool, Example::Endpoint::Endpoint1Response> processRequest1(Example::Endpoint::Endpoint1Request &request) = 0;

            // Add any additional methods or members specific to the service here.
        };
    } // namespace Endpoint
} // namespace Example