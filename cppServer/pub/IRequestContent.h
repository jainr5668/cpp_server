#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

namespace Server
{
    class IRequestContent
    {
    public:
        template <typename T>
        T* getBody()
        {
            T *body = nullptr;
            auto requestBody = getRawBody();
            if (!requestBody.empty())
            {
                try
                {
                    body = new T();
                    // auto jsonBody = nlohmann::json::parse(requestBody);
                    body->build(requestBody);
                }
                catch (const std::exception &e)
                {
                    throw std::runtime_error("Failed to parse request body: " + std::string(e.what()));
                }
            }
            return body;
        }
        virtual std::string getRawBody() = 0;
        virtual std::unordered_map<std::string, std::string> getHeaders() = 0;
        virtual std::string getMethod() = 0;
        virtual std::unordered_map<std::string, std::string> getQueryParameters() = 0;
        virtual std::string getRoute() = 0;
        virtual void setBody(std::string body) = 0;
        virtual void setHeaders(std::unordered_map<std::string, std::string> headers) = 0;
        virtual void setMethod(std::string method) = 0;
        virtual void setQueryParameters(std::unordered_map<std::string, std::string> queryParameters) = 0;
        virtual void setRoute(std::string route) = 0;
    }; // namespace IRequestContent
} // namespace Server
