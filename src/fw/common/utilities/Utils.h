#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class Utils
{
public:
    static std::string getValueFromMap(std::unordered_map<std::string, std::string> map, std::string key, std::string defaultValue)
    {
        auto value = map.find(key);
        if (value != map.end())
        {
            return value->second;
        }
        return defaultValue;
    }
    static std::string get_uuid()
    {
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        return boost::uuids::to_string(uuid);
    }
};