#pragma once

#include <IAuthorization.h>
#include <string>
#include <unordered_map>
#include "logger.h"

class Authorization : public IAuthorization {
public:
    Authorization();
    void setAuthorizationToken(const std::string authorization_token);
    std::unordered_map<std::string, std::string>* isAuthorized();
    std::string createToken(const std::unordered_map<std::string, std::string>& payload);
    std::unordered_map<std::string, std::string>* validateToken(const std::string& token);
private:
    std::string authorization_token_;
    const std::string secret = "CXlL52nd68sBwZvD7lQTsx4gc7E4th+h+ETgMz5pVd8=";
    Logger logger; 
};