#include "Authorization.h"
#include <jwt-cpp/jwt.h>
#include <vector>
#include <random>
#include <sstream>
#include <iomanip>

using Server::Authorization;

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
        try
        {
            if (token_.empty()) {
                logger.error("Authorization::isAuthenticated - Token is empty");
                throw std::runtime_error("Token is empty");
            }
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
}