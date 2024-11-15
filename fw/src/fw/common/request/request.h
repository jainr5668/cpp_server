#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Utils.h"
#include <Authorization.h>

class Request {
public:
    std::string method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::unordered_map<std::string, std::string> query_params;
    std::string body;
    Authorization* authorization = nullptr;

    Request(const std::string& raw_request);

private:
    void parse(const std::string& raw_request);

    void parseQueryParams(const std::string& query_string);

    std::vector<std::string> split(const std::string& s, char delimiter);
    Utils utils_;
};