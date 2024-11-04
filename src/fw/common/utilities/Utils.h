#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <unordered_map>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>

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

    /**
     * Convert time_point to string
     */
    static std::string timepoint_to_string(const std::chrono::system_clock::time_point &tp, std::string dtFormat = "%Y-%m-%dT%H:%M:%S")
    {
        auto time = std::chrono::system_clock::to_time_t(tp);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), dtFormat.c_str());
        return ss.str();
    }

    /**
     * Convert string to time_point
     */
    static std::chrono::system_clock::time_point string_to_timepoint(const std::string &str, std::string dtFormat = "%Y-%m-%dT%H:%M:%S")
    {
        std::tm tm = {};
        std::stringstream ss(str);
        ss >> std::get_time(&tm, dtFormat.c_str());
        return std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }

    /**
     * String to unordered_map
     */
    static nlohmann::json string_to_json(const std::string &str)
    {
        return nlohmann::json::parse(str);
    }
};