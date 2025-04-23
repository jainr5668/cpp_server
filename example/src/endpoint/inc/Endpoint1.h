#pragma once
#include "IEndpoint1.h"
#include "ServerTypes.h"
#include "Endpoint1Service.h"

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
            Endpoint1Service m_service;
        };
    } // namespace Endpoint
} // namespace Example
