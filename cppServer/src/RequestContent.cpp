#include "RequestContent.h"
#include <sstream>
#include <iostream>

using RequestContent = Server::RequestContent;

namespace Server
{
    RequestContent::RequestContent(std::string rawRequest)
    {
        parseRequest(rawRequest);
    }

    void RequestContent::parseRequest(std::string rawRequest)
    {
        std::cout << "Request: " << rawRequest << std::endl;
        std::vector<std::string> lines = splitString(rawRequest, '\n');
        std::vector<std::string> requestLine = splitString(lines[0], ' ');
        method = requestLine[0];
        route = requestLine[1];
        queryParameters = parseQueryParameters(route);
        headers = parseHeaders(lines[1]);
        body = lines[lines.size() - 1];
    }

    std::unordered_map<std::string, std::string> RequestContent::parseQueryParameters(std::string query)
    {
        std::vector<std::string> queryParts = splitString(query, '?');
        std::unordered_map<std::string, std::string> queryParameters_;
        if (queryParts.size() > 1)
        {
            std::vector<std::string> parameters = splitString(queryParts[1], '&');
            for (auto parameter : parameters)
            {
                std::vector<std::string> keyValue = splitString(parameter, '=');
                queryParameters_[keyValue[0]] = keyValue[1];
            }
        }
        return queryParameters_;
    }

    std::unordered_map<std::string, std::string> RequestContent::parseHeaders(std::string headers)
    {
        std::vector<std::string> headerLines = splitString(headers, '\n');
        std::unordered_map<std::string, std::string> headers_;
        for (auto headerLine : headerLines)
        {
            std::vector<std::string> header = splitString(headerLine, ':');
            if (header.size() > 1)
            {
                headers_[header[0]] = header[1];
            }
        }
        return headers_;
    }

    std::vector<std::string> RequestContent::splitString(std::string str, char delimiter)
    {
        std::vector<std::string> parts;
        std::string part;
        std::istringstream stream(str);
        while (std::getline(stream, part, delimiter))
        {
            parts.push_back(part);
        }
        return parts;
    }
}
