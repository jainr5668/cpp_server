#include "Authentication.h"
#include <jwt-cpp/jwt.h>
#include <vector>
#include <random>
#include <sstream>
#include <iomanip>
#include <memory>
#include "Authorization.h"

using Authentication = Server::Authentication;
using IAuthorization = Server::IAuthorization;
using Authorization = Server::Authorization;

namespace Server
{
    Authentication::Authentication()
    {
        if(secret.empty()) { secret = generateRandomSecret(); 
        std::cout << "secret: " << secret << std::endl; };
        payload_ = std::unordered_map<std::string, std::string>();
        token_ = "";
    }

    /**
     * Defination of virtual functions
     */
    std::unique_ptr<IAuthorization> Authentication::getAuthorization(std::string token)
    {
        std::unique_ptr<IAuthorization> iAuthorization = nullptr;
        if (!token.empty())
        {
            iAuthorization = std::make_unique<Authorization>(secret, token);
            
        }
        return iAuthorization;
    }

    std::unordered_map<std::string, std::string> Authentication::getPayload()
    {
        return payload_;
    }

    std::string Authentication::generateRandomSecret(size_t length)
    {
        // Use a secure random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        
        // Create a buffer for the bytes
        std::vector<unsigned char> buffer(length);
        for (size_t i = 0; i < length; i++) {
            buffer[i] = static_cast<unsigned char>(dis(gen));
        }
        
        // Convert bytes to hexadecimal string
        std::stringstream ss;
        for (const auto& byte : buffer) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        }
        
        return ss.str();
    }
}