#pragma once
#include <string>
#include <nlohmann/json.hpp>

class IData
{
public:
    template <typename T>
    std::string objectToJson(const T &obj)
    {
        nlohmann::json j = obj;
        return j.dump();
    }
};