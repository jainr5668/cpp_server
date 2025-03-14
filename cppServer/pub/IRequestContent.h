#pragma once
#include <string>
#include <unordered_map>

namespace Server
{
    class IRequestContent
    {
    public:
        virtual std::string getBody() = 0;
        virtual std::unordered_map<std::string, std::string> getHeaders() = 0;
        virtual std::string getMethod() = 0;
        virtual std::unordered_map<std::string, std::string> getQueryParameters() = 0;
        virtual std::string getRoute() = 0;
        virtual void setBody(std::string body) = 0;
        virtual void setHeaders(std::unordered_map<std::string, std::string> headers) = 0;
        virtual void setMethod(std::string method) = 0;
        virtual void setQueryParameters(std::unordered_map<std::string, std::string> queryParameters) = 0;
        virtual void setRoute(std::string route) = 0;
    };

}