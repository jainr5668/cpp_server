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
    }

    std::string Authorization::createToken(const std::unordered_map<std::string, std::string> &payload)
    {
        auto token = jwt::create()
                         .set_issuer("auth0")
                         .set_type("JWT")
                         .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{24});
        for (const auto &[key, value] : payload)
        {
            token.set_payload_claim(key, jwt::claim(value));
        }
        return token.sign(jwt::algorithm::hs256{secret});
    }

    std::unordered_map<std::string, std::string> Authorization::getPayload()
    {
        if (payload_.empty())
        {
            isAuthenticated();
        }
        return payload_;
    }

    bool Authorization::isAuthenticated()
    {
        bool result = false;
        try
        {
            auto decoded = jwt::decode(token_);
            auto verifier = jwt::verify()
                                .allow_algorithm(jwt::algorithm::hs256{secret})
                                .with_issuer("auth0");
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
            std::cout << "Authorization::validateToken " + std::string(e.what()) << std::endl;
        }
        return result;
    }
}