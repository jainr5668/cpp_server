#include "Authorization.h"
#include <jwt-cpp/jwt.h>
#include <vector>
#include <random>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using Server::Authorization;

int Server::Authorization::counter_ = 0;
namespace Server
{
    Authorization::Authorization(std::string secret, std::string token) : secret(secret), token_(token)
    {
        logger.info("Authorization constructor called");
    }

    std::string Authorization::createToken(const std::unordered_map<std::string, std::string> &payload)
    {
        logger.info("Authorization::createToken - entering");
        auto token = jwt::create()
                         .set_issuer("auth0")
                         .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{24});
        for (const auto &[key, value] : payload)
        {
            token.set_payload_claim(key, jwt::claim(value));
        }
        token.set_payload_claim("counter", jwt::claim(std::to_string(counter_++)));
        token_ = token.sign(jwt::algorithm::hs256{secret});
        logger.info("Authorization::createToken - exiting");
        return token_;
    }

    std::unordered_map<std::string, std::string> Authorization::getPayload()
    {
        logger.info("Authorization::getPayload - entering");
        if (payload_.empty())
        {
            isAuthenticated();
        }
        logger.info("Authorization::getPayload - exiting");
        return payload_;
    }

    bool Authorization::isAuthenticated()
    {
        logger.info("Authorization::isAuthenticated - entering");
        bool result = false;
        if (token_.empty())
        {
            logger.error("Authorization::isAuthenticated - Token is empty");
            throw std::runtime_error("Token is empty");
        }
        try
        {
                auto verifier = jwt::verify()
                                    .with_issuer("auth0")
                                    .allow_algorithm(jwt::algorithm::hs256{secret});
                auto decoded = jwt::decode(token_);
                verifier.verify(decoded);
                payload_.clear();
                for (auto &[key, value] : decoded.get_payload_claims())
                {
                    payload_.insert({key, value.to_json().to_str()});
                }
                result = true;
        }
        catch (const std::exception &e)
        {
            logger.error("Authorization::isAuthenticated - " + std::string(e.what()));
        }
        logger.info("Authorization::isAuthenticated - exiting");
        return result;
    }

    std::unordered_map<std::string, std::string> Authorization::getPayload(std::string token)
    {
        logger.info("Authorization::getPayload(token) - entering");
        std::unordered_map<std::string, std::string> tempPayload;
        try
        {
            if (token.empty())
            {
                logger.error("Authorization::getPayload(token) - Token is empty");
                throw std::runtime_error("Token is empty");
            }
            auto verifier = jwt::verify()
                                .with_issuer("auth0")
                                .allow_algorithm(jwt::algorithm::hs256{secret});
            auto decoded = jwt::decode(token);
            verifier.verify(decoded);
            for (auto &[key, value] : decoded.get_payload_claims())
            {
                tempPayload.insert({key, value.to_json().to_str()});
            }
        }
        catch (const std::exception &e)
        {
            logger.error("Authorization::getPayload(token) - " + std::string(e.what()));
        }
        logger.info("Authorization::getPayload(token) - exiting");
        return tempPayload;
    }
}