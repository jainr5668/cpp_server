#pragma once

#include "IRequestContent.h"

#include <string>
#include <unordered_map>
#include <vector>

using IRequestContent = Server::IRequestContent;

namespace Server
{
    class RequestContent : public IRequestContent
    {
    public:
        RequestContent() = default;
        RequestContent(std::string rawRequest);
        std::string getBody() { return body; }
        std::unordered_map<std::string, std::string> getHeaders() { return headers; }
        std::string getMethod() { return method; }
        std::unordered_map<std::string, std::string> getQueryParameters() { return queryParameters; }
        std::string getRoute() { return route; }
        void setBody(std::string body) { this->body = body; }
        void setHeaders(std::unordered_map<std::string, std::string> headers) { this->headers = headers; }
        void setMethod(std::string method) { this->method = method; }
        void setQueryParameters(std::unordered_map<std::string, std::string> queryParameters) { this->queryParameters = queryParameters; }
        void setRoute(std::string route) { this->route = route; }

    private:
        std::string body;
        std::unordered_map<std::string, std::string> headers;
        std::string method;
        std::unordered_map<std::string, std::string> queryParameters;
        std::string route;
        std::unordered_map<std::string, std::string> parseHeaders(std::string headers);
        std::unordered_map<std::string, std::string> parseQueryParameters(std::string query);
        void parseRequest(std::string rawRequest);
        std::vector<std::string> splitString(std::string str, char delimiter);
    }; // class RequestContent
} // namespace Server
