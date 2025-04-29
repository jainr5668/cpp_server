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
        case 401:
            return "Unauthorized";
        case 404:
            return "Not Found";
        default:
            return "Internal Server Error";
        }
    }
    void ResponseContent::setAuthorizationHandler(std::unique_ptr<IAuthorization> authHandler)
    {
        this->authorizationHandler = std::move(authHandler);
    }

} // namespace Server