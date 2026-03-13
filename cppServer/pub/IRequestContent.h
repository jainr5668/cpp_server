#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace Server
{
    class IRequestContent
    {
    public:
        nlohmann::json getBody()
        {
            nlohmann::json body;
            auto requestBody = getRawBody();
            if (!requestBody.empty())
            {
                try
                {
                    body = nlohmann::json::parse(requestBody);
                }
                catch (const std::exception &e)
                {
                    throw std::runtime_error("Failed to parse request body: " + std::string(e.what()));
                }
            }
            return body;
        }

        template <typename T>
        std::unique_ptr<T> getBody()
        {
            try
            {
                auto json = getBody();
                return std::make_unique<T>(json);
            }
            catch (const std::exception &e)
            {
                return nullptr;
            }
        }
        virtual std::string getRawBody() = 0;
        virtual std::unordered_map<std::string, std::string> getHeaders() = 0;
        virtual std::string getMethod() = 0;
        virtual std::unordered_map<std::string, std::string> getQueryParameters() = 0;
        virtual std::string getRoute() = 0;
        virtual int getRouteDepth() = 0;
        virtual std::vector<std::string> getRequestBodyParts() = 0;
        virtual std::string getRequestBodyPart(std::string partName) = 0;
        virtual std::unordered_map<std::string, std::string> getPathParams() = 0;
        virtual void setBody(std::string body) = 0;
        virtual void setHeaders(std::unordered_map<std::string, std::string> headers) = 0;
        virtual void setMethod(std::string method) = 0;
        virtual void setQueryParameters(std::unordered_map<std::string, std::string> queryParameters) = 0;
        virtual void setRoute(std::string route) = 0;
        virtual void setRouteDepth(int depth) = 0;
        virtual void setPathParams(std::unordered_map<std::string, std::string> pathParams) = 0;
        virtual std::map<std::string, std::string> getFormFields() const = 0;
        virtual std::map<std::string, std::pair<std::string, std::string>> getFiles() const = 0;
    }; // namespace IRequestContent
} // namespace Server
