#include <sstream>
#include "ResponseContent.h"

using ResponseContent = Server::ResponseContent;

namespace Server
{

    std::string ResponseContent::getServerResponse()
    {
        std::ostringstream response;
        response << "HTTP/1.1 " << statusCode << " " << getStatusText() << "\n";
        for (auto header : headers)
        {
            response << header.first << ": " << header.second << "\n";
        }
        response << "Content-Length: " << body.size() << "\n\n";
        response << body;
        return response.str();
    }
    std::string ResponseContent::getStatusText()
    {
        switch (statusCode)
        {
        case 200:
            return "OK";
        case 201:
            return "Created";
        case 202:
            return "Accepted";
        case 204:
            return "No Content";
        case 206:
            return "Partial Content";
        case 400:
            return "Bad Request";
        case 401:
            return "Unauthorized";
        case 404:
            return "Not Found";
        case 403:
            return "Forbidden";
        case 405:
            return "Method Not Allowed";
        case 500:
            return "Internal Server Error";
        case 503:
            return "Service Unavailable";
        case 504:
            return "Gateway Timeout";
        case 502:
            return "Bad Gateway";
        default:
            return "Internal Server Error";
        }
    }
    void ResponseContent::setAuthorizationHandler(std::unique_ptr<IAuthorization> authHandler)
    {
        this->authorizationHandler = std::move(authHandler);
    }

} // namespace Server