#pragma once

#include <string>
#include <unordered_map>
#include <IAuthorization.h>

using IAuthorization = Server::IAuthorization;

namespace Server{
    class IResponseContent
    {
    public:
        virtual std::string getBody() = 0;
        virtual std::unordered_map<std::string, std::string> getHeaders() = 0;
        virtual int getStatusCode() = 0;
        virtual std::string getServerResponse() = 0;
        virtual std::string getStatusText() = 0;
        virtual void setBody(std::string body) = 0;
        virtual void setHeaders(std::unordered_map<std::string, std::string> headers) = 0;
        virtual void setStatusCode(int statusCode) = 0;
        virtual void setAuthorizationHandler(std::unique_ptr<IAuthorization> authHandler) = 0;
    }; // namespace IResponseContent
} // namespace Server
