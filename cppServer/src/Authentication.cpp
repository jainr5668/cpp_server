#include "Authentication.h"

using Authentication = Server::Authentication;

namespace Server
{

    /**
     * Defination of private functions
     */

    bool Authentication::isTokenValid()
    {
        return !token_.empty();
    }

    /**
     * Defination of virtual functions
     */
    std::string Authentication::getAuthorizationToken()
    {
        return token_;
    }

    std::unordered_map<std::string, std::string> Authentication::getPayload()
    {
        return payload_;
    }

    bool Authentication::isAuthenticated()
    {
        return isTokenValid();
    }

    void Authentication::setAuthorizationToken(const std::string authorization_token)
    {
        token_ = authorization_token;
    }

}