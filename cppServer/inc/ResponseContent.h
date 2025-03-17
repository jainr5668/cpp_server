#pragma once

#include "IResponseContent.h"

using IResponseContent = Server::IResponseContent;

namespace Server{
    class ResponseContent : public IResponseContent
    {
    public:
        ResponseContent() = default;
        ResponseContent(std::string body, std::unordered_map<std::string, std::string> headers, int statusCode):body(body), headers(headers), statusCode(statusCode) {};
        std::string getBody() { return body; }
        std::unordered_map<std::string, std::string> getHeaders() { return headers; }
        int getStatusCode() { return statusCode; }
        std::string getStatusText();
        std::string getServerResponse();
        void setBody(std::string body) { this->body = body; }
        void setHeaders(std::unordered_map<std::string, std::string> headers) { this->headers = headers; }
        void setStatusCode(int statusCode) { this->statusCode = statusCode; }
    private:
        std::string body;
        std::unordered_map<std::string, std::string> headers;
        int statusCode;
    }; // class ResponseContent
} // namespace Server
