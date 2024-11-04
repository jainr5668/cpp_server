#include "router.h"
#include "Utils.h"

void Router::addRoute(Route route)
{
    routes.push_back(route);
}
void Router::addSubRouter(const std::string &path, std::unique_ptr<IRouter> subrouter_)
{
    subRoutes[path] = std::move(subrouter_);
}
void Router::handle_request(Request *req, Response *res)
{
    // logger.info("Processing request: " + req->path + " Method: " + req->method);
    // for (auto route : routes)
    // {
    //     logger.info("Route: " + route.path + " Method: " + requestMethodToString(route.method));
    // }
    std::vector<std::string> seglist;
    std::string segment;
    std::stringstream test(req->path);
    std::map<std::string, std::string> path_params;
    while (std::getline(test, segment, '/'))
    {
        seglist.push_back(segment);
    }
    if (seglist.size()>0 && seglist[0] == ""){
        seglist.erase(seglist.begin());
    }
    for (auto &subRouter : subRoutes)
    {
        if (seglist[0].find(subRouter.first) == 0)
        {
            req->path = req->path.substr(subRouter.first.length() + 1);
            subRouter.second->handle_request(req, res);
            return;
        }
    }
    bool routeFound = false;
    for (const auto &route : routes)
    {
        std::regex pattern(routeToRegex(route.path));
        std::smatch matches;
        if (std::regex_match(req->path, matches, pattern))
        {
            routeFound = true;
            if (req->method == requestMethodToString(route.method))
            {
                if (route.authConfig.enabled)
                {
                    if (req->authorization->isAuthorized() == nullptr)
                    {
                        res->status_code = 401;
                        res->body = "Unauthorized";
                        return;
                    }
                    std::unordered_map<std::string, std::string> authMap = *(req->authorization->isAuthorized());
                    std::string accessLevel = Utils::getValueFromMap(authMap, "accessLevel", "");
                    std::string scope = Utils::getValueFromMap(authMap, "scope", "");
                    bool accessLevelMatch = true;
                    bool scopeMatch = true;
                    if (route.authConfig.accessLevels.size() > 0)
                    {
                        accessLevelMatch = false;
                        for (auto &level : route.authConfig.accessLevels)
                        {
                            if (level == accessLevel)
                            {
                                accessLevelMatch = true;
                                break;
                            }
                        }
                        if (!accessLevelMatch) logger.error("Access Level not Matched: " + accessLevel);
                    }
                    if (route.authConfig.scope.size() > 0)
                    {
                        scopeMatch = false;
                        for (auto &s : route.authConfig.scope)
                        {
                            if (s == scope)
                            {
                                scopeMatch = true;
                                break;
                            }
                        }
                        if (!scopeMatch) logger.error("Scope not Matched: " + scope);
                    }
                    if (!accessLevelMatch || !scopeMatch)
                    {
                        res->status_code = 403;
                        res->body = "Forbidden";
                        return;
                    }
                }
                std::map<std::string, std::string> params;
                std::vector<std::string> paramNames = extractParamNames(route.path);
                for (size_t i = 1; i < matches.size() && i <= paramNames.size(); ++i)
                {
                    params[paramNames[i - 1]] = matches[i].str();
                }
                RouteContext routeContext;
                routeContext.req = req;
                routeContext.res = res;
                routeContext.path_params = params;
                route.handler(routeContext);
                return;
            }
        }
    }
    if (routeFound)
    {
        res->status_code = 405;
        res->body = "Method Not Allowed";
        logger.error(req->method + " Method Not Allowed");
    }
    else
    {
        res->status_code = 404;
        res->body = "Not Found";
        logger.error(req->path + " Not Found");
    }
}

std::string Router::requestMethodToString(RouteMethod method)
{
    std::string methodStr;
    switch (method)
    {
    case RouteMethod::GET:
        methodStr = "GET";
        break;
    case RouteMethod::POST:
        methodStr = "POST";
        break;
    case RouteMethod::PUT:
        methodStr = "PUT";
        break;
    case RouteMethod::DELETE:
        methodStr = "DELETE";
        break;
    case RouteMethod::PATCH:
        methodStr = "PATCH";
        break;
    default:
        methodStr = "GET";
    }
    return methodStr;
}

std::string Router::routeToRegex(const std::string &route)
{
    std::ostringstream oss;
    oss << "^";
    std::istringstream iss(route);
    std::string segment;
    while (std::getline(iss, segment, '/'))
    {
        if (segment.empty())
            continue;
        if (segment[0] == ':')
        {
            oss << "/([^/]+)";
        }
        else
        {
            oss << "/" << segment;
        }
    }
    oss << "$";
    return oss.str();
}

std::vector<std::string> Router::extractParamNames(const std::string &route)
{
    std::vector<std::string> names;
    std::istringstream iss(route);
    std::string segment;
    while (std::getline(iss, segment, '/'))
    {
        if (segment.empty())
            continue;
        if (segment[0] == ':')
        {
            names.push_back(segment.substr(1));
        }
    }
    return names;
}