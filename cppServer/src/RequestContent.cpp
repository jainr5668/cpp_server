#include "RequestContent.h"
#include <sstream>
#include <algorithm>

using RequestContent = Server::RequestContent;

namespace Server
{

    RequestContent::RequestContent(std::string rawRequest)
    {
        logger.info("RequestContent::RequestContent - entering");
        parseRequest(rawRequest);
        logger.info("RequestContent::RequestContent - exiting");
    }

    void RequestContent::parseRequest(std::string rawRequest)
    {
        logger.info("RequestContent::parseRequest - entering");
        std::istringstream stream(rawRequest);
        std::string line;
        std::getline(stream, line);
        std::vector<std::string> requestParts = splitString(line, ' ');
        if (requestParts.size() < 3)
            return;
        method = requestParts[0];
        route = requestParts[1];
        queryParameters = parseQueryParameters(route);
        std::string headerString;
        while (std::getline(stream, line))
        {
            if (line == "\r")
                break;
            headerString += line + "\n";
        }
        headers = parseHeaders(headerString);
        while (std::getline(stream, line))
        {
            body += line + "\n";
        }
        logger.info("RequestContent::parseRequest - exiting");
    }

    std::unordered_map<std::string, std::string> RequestContent::parseQueryParameters(std::string query)
    {
        logger.info("RequestContent::parseQueryParameters - entering");
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
        logger.info("RequestContent::parseQueryParameters - exiting");
        return queryParameters_;
    }

    std::unordered_map<std::string, std::string> RequestContent::parseHeaders(std::string headers)
    {
        logger.info("RequestContent::parseHeaders - entering");
        std::vector<std::string> headerLines = splitString(headers, '\n');
        std::unordered_map<std::string, std::string> headers_;
        for (auto headerLine : headerLines)
        {
            headerLine.erase(std::remove(headerLine.begin(), headerLine.end(), '\r'), headerLine.end());
            std::vector<std::string> header = splitString(headerLine, ':');
            if (header.size() > 1)
            {
                headers_[header[0]] = header[1];
            }
        }
        logger.info("RequestContent::parseHeaders - exiting");
        return headers_;
    }

    std::vector<std::string> RequestContent::splitString(std::string str, char delimiter)
    {
        logger.info("RequestContent::splitString - entering");
        std::vector<std::string> parts;
        std::string part;
        std::istringstream stream(str);
        while (std::getline(stream, part, delimiter))
        {
            parts.push_back(part);
        }
        logger.info("RequestContent::splitString - exiting");
        return parts;
    }

}
