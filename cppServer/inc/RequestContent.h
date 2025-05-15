#pragma once

#include "IRequestContent.h"
#include "logger.h"

#include <nlohmann/json.hpp>
#include <string>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

using IRequestContent = Server::IRequestContent;
using Logger = Server::Logger;

namespace Server
{
    class RequestContent : public IRequestContent
    {
    public:
        RequestContent() = default;
        RequestContent(std::string rawRequest);

        /**
         * @brief Gets the raw request body
         * 
         * @return std::string
         */
        std::string getRawBody() { return body; }

        /**
         * @brief Gets the request headers
         * 
         * @return std::unordered_map<std::string, std::string>
         */
        std::unordered_map<std::string, std::string> getHeaders() { return headers; }

        /**
         * @brief Gets the request method
         * 
         * @return std::string
         */
        std::string getMethod() { return method; }

        /**
         * @brief Gets the request query parameters
         * 
         * @return std::unordered_map<std::string, std::string>
         */
        std::unordered_map<std::string, std::string> getQueryParameters() { return queryParameters; }

        /**
         * @brief Gets the request route
         * 
         * @return std::string
         */
        std::string getRoute() { return route; }

        /**
         * @brief Sets the request body
         * 
         * @param body std::string
         */
        void setBody(std::string body) { this->body = body; }

        /**
         * @brief Sets the request headers
         * 
         * @param headers std::unordered_map<std::string, std::string>
         */
        void setHeaders(std::unordered_map<std::string, std::string> headers) { this->headers = headers; }

        /**
         * @brief Sets the request method
         * 
         * @param method std::string
         */
        void setMethod(std::string method) { this->method = method; }

        /**
         * @brief Sets the request query parameter
         * 
         * @param queryParameters std::unordered_map<std::string, std::string>
         */
        void setQueryParameters(std::unordered_map<std::string, std::string> queryParameters) { this->queryParameters = queryParameters; }

        /**
         * @brief Sets the request route
         * 
         * @param route std::string
         */
        void setRoute(std::string route) { this->route = route; }

    private:
        std::string body;
        std::unordered_map<std::string, std::string> headers;
        Logger logger;
        std::string method;
        std::unordered_map<std::string, std::string> queryParameters;
        std::string route;

        /**
         * @brief Parses the header string to unordered map
         * 
         * @param headers std::string
         * @return std::unordered_map<std::string, std::string>
         */
        std::unordered_map<std::string, std::string> parseHeaders(std::string headers);

        /**
         * @brief Parshes the query string to unordered map
         * 
         * @param query std::string
         * @returns std::unordered_map<std::string, std::string>
         */
        std::unordered_map<std::string, std::string> parseQueryParameters(std::string query);

        /**
         * @brief Parses the string from raw request
         * 
         * @param rawRequest std::string
         */
        void parseRequest(std::string rawRequest);

        /**
         * @brief Splits the string by delimiter
         * 
         * @param str std::string
         * @param delimiter char
         * @returns std::vector<std::string>
         */
        std::vector<std::string> splitString(std::string str, char delimiter);

    }; // class RequestContent
} // namespace Server
