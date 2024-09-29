#include "Authorization.h"
#include <jwt-cpp/jwt.h>
Authorization::Authorization()
{}

std::unordered_map<std::string, std::string>* Authorization::isAuthorized()
{
    return validateToken(authorization_token_);
}

void Authorization::setAuthorizationToken(std::string authorization_token)
{
    authorization_token_ = authorization_token;
}

std::string Authorization::createToken(const std::unordered_map<std::string, std::string>& payload) {
    auto token = jwt::create()
        .set_issuer("auth0")
        .set_type("JWS")
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{24});
    for (const auto& [key, value] : payload) {
        token.set_payload_claim(key, jwt::claim(value));
    }
    return token.sign(jwt::algorithm::hs256{secret});
}

std::unordered_map<std::string, std::string>* Authorization::validateToken(const std::string& token) {
    std::unordered_map<std::string, std::string>* payload = nullptr;
    try {
        auto decoded = jwt::decode(token);
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{secret})
            .with_issuer("auth0");
        verifier.verify(decoded);
        payload = new std::unordered_map<std::string, std::string>();
        for (auto& [key, value] : decoded.get_payload_claims()) {
            payload->insert({key, value.to_json().to_str()});
        }
    } catch (const std::exception& e) {
        logger.error("Authorization::validateToken " + std::string(e.what()));
    }
    return payload;
}