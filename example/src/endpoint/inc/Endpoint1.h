#pragma once
#include "IEndpoint1.h"
#include "ServerTypes.h"

namespace Example
{
    namespace Endpoint
    {
        class Endpoint1 : public IEndpoint1
        {
        public:
            Endpoint1();
            ~Endpoint1() = default;

        private:
            void function1(Server::ServerTypes::RouteContext context);
        };
    } // namespace Endpoint
} // namespace Example
