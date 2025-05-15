#include <iostream>

#include "Endpoint1.h"

#include "ServerTypes.h"
#include "Endpoint1Types.h"
#include <nlohmann/json.hpp>

namespace Example
{
    namespace Endpoint
    {
        Endpoint1::Endpoint1()
        {
            Server::ServerTypes::AuthorizationConfiguration authorizationConfiguration;
            authorizationConfiguration.enabled = false;
            authorizationConfiguration.scopes = {};
            authorizationConfiguration.accessLevels = {};
            Server::ServerTypes::Route route;
            route.type = Server::ServerTypes::RouteType::POST;
            route.route = "/test";
            route.authorization = authorizationConfiguration;
            route.handler = std::bind(&Endpoint1::function1, this, std::placeholders::_1);
            Server::ServerTypes::AuthorizationConfiguration authorizationConfiguration1;
            authorizationConfiguration1.enabled = true;
            authorizationConfiguration1.scopes = {"scope1", "scope2"};
            authorizationConfiguration1.accessLevels = {};
            Server::ServerTypes::Route route1;
            route1.type = Server::ServerTypes::RouteType::POST;
            route1.route = "/test1";
            route1.authorization = authorizationConfiguration1;
            route1.handler = std::bind(&Endpoint1::function1, this, std::placeholders::_1);
            addRoute(route);
            addRoute(route1);
        }

        void Endpoint1::function1(Server::ServerTypes::RouteContext context)
        {
            std::cout << "Endpoint1::function1 - entering" << std::endl;
            auto requestBody = context.requestContext->getBody<Example::Endpoint::Endpoint1Request>();
            if (!requestBody)
            {
                context.responseContext->setStatusCode(400);
                context.responseContext->setBody("Bad Request");
                std::cout << "Endpoint1::function1 - exiting" << std::endl;
                return;
            }
            auto token = context.responseContext->createToken({{"scope", "scope1"}});
            auto response = m_service.processRequest1(*requestBody);
            nlohmann::json responseJson;
            responseJson["token"] = token;
            if (response.first)
            {
                context.responseContext->setStatusCode(200);
                context.responseContext->setBody(responseJson.dump(4));
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
