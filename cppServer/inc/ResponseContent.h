#pragma once

#include "IResponseContent.h"

using IResponseContent = Server::IResponseContent;

namespace Server
{
    class ResponseContent : public IResponseContent
    {
    public:
        ResponseContent() = default;
        ResponseContent(std::string body, std::unordered_map<std::string, std::string> headers, int statusCode) : body(body), headers(headers), statusCode(statusCode) {};

        /**
         * @brief Gets the response body
         *
         * @returns std::string
         */
        std::string getBody() { return body; }

        /**
         * @brief Gets the response headers
         *
         * @returns std::unordered_map<std::string, std::string>
         */
        std::unordered_map<std::string, std::string> getHeaders() { return headers; }

        /**
         * @brief Gets the response status code
         *
         * @return int
         */
        int getStatusCode() { return statusCode; }

        /**
         * @brief Gets the server reaponse that has to be sent back to client
         *
         * @returns std::string
         */
        std::string getServerResponse();

        /**
         * @brief Sets the response body
         *
         * @param body std::string
         */
        void setBody(std::string body) { this->body = body; }

        /**
         * @brief Setd the response headers
         *
         * @param headers std::unordered_map<std::string, std::string>
         */
        void setHeaders(std::unordered_map<std::string, std::string> headers) { this->headers = headers; }

        /**
         * @brief Sets the reaponse status code
         *
         * @param statusCode int
         */
        void setStatusCode(int statusCode) { this->statusCode = statusCode; }

    private:
        std::string body;
        std::unordered_map<std::string, std::string> headers;
        int statusCode;

        /**
         * @brief Gets the status text
         *
         * @return std::string
         */
        std::string getStatusText();

    }; // class ResponseContent
} // namespace Server
