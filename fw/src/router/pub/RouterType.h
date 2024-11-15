#pragma once
#include <string>
#include <functional>
#include "response.h"
#include <map>
#include "request.h"
#include "AuthorizationTypes.h"

enum RouteMethod{
    GET = 0,
    POST,
    PUT,
    DELETE,
    PATCH,
    OPTIONS
};

struct RouteContext {
    Request *req;
    Response *res;
    std::map<std::string, std::string> path_params;
};

struct Route{
    std::string path;
    RouteMethod method;
    common::authorization::AuthorizationConfig authConfig;
    std::function<void(RouteContext)> handler;
};