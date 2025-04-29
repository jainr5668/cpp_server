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
            authorizationConfiguration.scopes = {};
            authorizationConfiguration.accessLevels = {};
            Server::ServerTypes::Route route;
            route.type = Server::ServerTypes::RouteType::POST;
            route.route = "/test";
            route.authorization = authorizationConfiguration;
            route.handler = std::bind(&Endpoint1::function1, this, std::placeholders::_1);
            addRoute(route);
        }
        void Endpoint1::function1(Server::ServerTypes::RouteContext context)
        {
            std::cout << "Endpoint1::function1 - entering" << std::endl;
            auto requestBody = context.requestContext->getBody<Example::Endpoint::Endpoint1Request>();

            auto response = m_service.processRequest1(*requestBody);
            if (response.first)
            {
                context.responseContext->setStatusCode(200);
                context.responseContext->setBody(response.second.toString(4));
            }
            else
            {
                context.responseContext->setStatusCode(500);
                context.responseContext->setBody("Internal Server Error");
            }
            std::cout << "Endpoint1::function1 - exiting" << std::endl;
            // Send the response
        }
    } // namespace Endpoint
} // namespace Example
