#pragma once
#include <vector>
#include <string>
#include <functional>
#include "IRequestContent.h"
#include "IResponseContent.h"

using IRequestContent = Server::IRequestContent;
using IResponseContent = Server::IResponseContent;

namespace Server
{
    namespace ServerTypes
    {
        enum class ServerType
        {
            HTTP,
            HTTPS
        };

        enum class RouteType
        {
            GET,
            POST,
            PUT,
            DELETE
        };

        struct RouteContext
        {
            IRequestContent *requestContext;
            IResponseContent *responseContext;
        };

        // template <typename T1, typename T2>
        // class RouteContextWrapper
        // {
        //     public:
        //     RouteContextWrapper(RouteContext &context)
        //         : requestContext(context.requestContext), responseContext(context.responseContext)
        //     {
        //     }
        //     RouteContextWrapper(const RouteContextWrapper &other)
        //         : requestContext(other.requestContext), responseContext(other.responseContext)
        //     {
        //     }
        //     RouteContextWrapper &operator=(const RouteContextWrapper &other)
        //     {
        //         if (this != &other)
        //         {
        //             requestContext = other.requestContext;
        //             responseContext = other.responseContext;
        //         }
        //         return *this;
        //     }
        //     IRequestContent *requestContext;
        //     IResponseContent *responseContext;
        //     T1 *getRequestContext()
        //     {
        //         T1 *requestBody = nullptr;
        //         requestJson = from_json<T1>(requestContext->getBody());
        //         if (requestJson != nullptr)
        //         {
        //             requestBody = static_cast<T1 *>(requestJson);
        //         }
        //         return requestBody;
        //     }
        //     T2 *getResponseContext()
        //     {
        //         return static_cast<T2 *>(responseContext->getBody());
        //     }
        //     void setResponseContext(T2 *response)
        //     {
        //         responseContext->setBody(toJson(response));
        //     }

        // };

        struct AuthorizationConfiguration
        {
            bool enabled;
            std::vector<std::string> accessLevels;
            std::vector<std::string> scopes;
        };

        struct Route
        {
            RouteType type;
            std::string route;
            AuthorizationConfiguration authorization;
            std::function<void(RouteContext)> handler;
        };
    } // namespace ServerTypes
} // namespace Server
