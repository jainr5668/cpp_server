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
        logger.info("Authentication::Authentication - entering");
        if(secret.empty()) { secret = generateRandomSecret(); }
        payload_ = std::unordered_map<std::string, std::string>();
        token_ = "";
        logger.info("Authentication::Authentication - exiting");
    }

    /**
     * Defination of virtual functions
     */
    std::unique_ptr<IAuthorization> Authentication::getAuthorization(std::string token)
    {
        logger.info("Authentication::getAuthorization - entering");
        logger.info("Authentication::getAuthorization - exiting");
        return std::make_unique<Authorization>(secret, token);
    }

    std::unordered_map<std::string, std::string> Authentication::getPayload()
    {
        logger.info("Authentication::getPayload - entering");
        logger.info("Authentication::getPayload - exiting");
        return payload_;
    }

    std::string Authentication::generateRandomSecret(size_t length)
    {
        logger.info("Authentication::generateRandomSecret - entering");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);

        std::vector<unsigned char> buffer(length);
        for (size_t i = 0; i < length; i++) {
            buffer[i] = static_cast<unsigned char>(dis(gen));
        }

        std::stringstream ss;
        for (const auto& byte : buffer) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        }
        logger.info("Authentication::generateRandomSecret - exiting");
        return ss.str();
    }
}