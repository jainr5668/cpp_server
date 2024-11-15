#include "request.h"
#include <thread>

Request::Request(const std::string &raw_request)
{
    parse(raw_request);
}

void Request::parse(const std::string &raw_request)
{
    std::istringstream stream(raw_request);
    std::string request_line;
    std::getline(stream, request_line);

    auto request_parts = split(request_line, ' ');
    if (request_parts.size() >= 2)
    {
        method = request_parts[0];
        auto path_and_query = split(request_parts[1], '?');
        path = path_and_query[0];
        if (path_and_query.size() > 1)
        {
            parseQueryParams(path_and_query[1]);
        }
    }

    std::string header_line;
    while (std::getline(stream, header_line) && header_line != "\r")
    {
        auto colon_pos = header_line.find(':');
        if (colon_pos != std::string::npos)
        {
            std::string key = header_line.substr(0, colon_pos);
            std::string value = header_line.substr(colon_pos + 2, header_line.length() - colon_pos - 3);
            headers[key] = value;
        }
    }
    auto authorization_token = utils_.getValueFromMap(headers, "Authorization", "Bearer ");
    if (authorization_token != "")
    {
        authorization_token.erase(0, 7);
        authorization = new Authorization();
        authorization->setAuthorizationToken(authorization_token);
    }

    std::string line;
    while (std::getline(stream, line))
    {
        body += line + "\n";
    }
}

void Request::parseQueryParams(const std::string &query_string)
{
    auto params = split(query_string, '&');
    for (const auto &param : params)
    {
        auto kv = split(param, '=');
        if (kv.size() == 2)
        {
            query_params[kv[0]] = kv[1];
        }
    }
}

std::vector<std::string> Request::split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}