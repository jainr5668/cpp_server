#include <sstream>
#include "ResponseContent.h"

using ResponseContent = Server::ResponseContent;

namespace Server
{

    std::string ResponseContent::getServerResponse()
    {
        logger.info("ResponseContent::getServerResponse - entering");
        std::ostringstream response;
        response << "HTTP/1.1 " << statusCode << " " << getStatusText() << "\n";
        for (auto header : headers)
        {
            response << header.first << ": " << header.second << "\n";
        }
        response << "Content-Length: " << body.size() << "\n\n";
        response << body;
        logger.info("ResponseContent::getServerResponse - exiting");
        return response.str();
    }
    std::string ResponseContent::getStatusText()
    {
        logger.info("ResponseContent::getStatusText - entering");
        std::string statusText;
        switch (statusCode)
        {
        case 200:
            statusText = "OK";
            break;
        case 201:
            statusText = "Created";
            break;
        case 202:
            statusText = "Accepted";
            break;
        case 204:
            statusText = "No Content";
            break;
        case 206:
            statusText = "Partial Content";
            break;
        case 400:
            statusText = "Bad Request";
            break;
        case 401:
            statusText = "Unauthorized";
            break;
        case 404:
            statusText = "Not Found";
            break;
        case 403:
            statusText = "Forbidden";
            break;
        case 405:
            statusText = "Method Not Allowed";
            break;
        case 500:
            statusText = "Internal Server Error";
            break;
        case 503:
            statusText = "Service Unavailable";
            break;
        case 504:
            statusText = "Gateway Timeout";
            break;
        case 502:
            statusText = "Bad Gateway";
            break;
        default:
            statusText = "Internal Server Error";
        }
        logger.info("ResponseContent::getStatusText - exiting");
        return statusText;
    }
    void ResponseContent::setAuthorizationHandler(std::unique_ptr<IAuthorization> authHandler)
    {
        logger.info("ResponseContent::setAuthorizationHandler - entering");
        if (!authHandler)
        {
            logger.error("Authorization handler is null");
        }
        else
        {
            this->authorizationHandler = std::move(authHandler);
        }
        logger.info("ResponseContent::setAuthorizationHandler - exiting");
    }

    std::string ResponseContent::createToken(const std::unordered_map<std::string, std::string> &payload)
    {
        logger.info("ResponseContent::createToken - entering");
        std::string token;
        if (authorizationHandler)
        {
            token = authorizationHandler->createToken(payload);
        }
        logger.error("Authorization handler not set");
        return token;
    }
} // namespace Server