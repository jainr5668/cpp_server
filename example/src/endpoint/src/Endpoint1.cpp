#include <iostream>

#include "Endpoint1.h"

#include "ServerTypes.h"
#include "Endpoint1Types.h"

namespace Example
{
    namespace Endpoint
    {
        Endpoint1::Endpoint1()
        {
            Server::ServerTypes::AuthorizationConfiguration authorizationConfiguration;
            authorizationConfiguration.enabled = true;
            Server::ServerTypes::Route route;
            route.type = Server::ServerTypes::RouteType::GET;
            route.route = "/test";
            route.authorization = authorizationConfiguration;
            route.handler = std::bind(&Endpoint1::function1, this, std::placeholders::_1);
            addRoute(route);
        }
        void Endpoint1::function1(Server::ServerTypes::RouteContext context)
        {
            // Example of how to use the request and response context
            // You can access the request body, headers, and other information
            std::cout << "Endpoint1::function1 - entering" << std::endl;
            auto requestBody = context.requestContext->getBody<Example::Endpoint::Endpoint1Response>();
            if (requestBody == nullptr)
            {
                context.responseContext->setStatusCode(400);
                context.responseContext->setBody("Invalid request body");
                return;
            }
            // Process the request
            std::cout << "Request Body: " << requestBody->getEndpoint1Request().value().getId().value() << std::endl;
            std::cout << "Request Body: " << requestBody->getMessage().has_value() << std::endl;

            context.responseContext->setStatusCode(200);
            context.responseContext->setBody("Hello from Endpoint route");
        }
    } // namespace Endpoint
} // namespace Example
