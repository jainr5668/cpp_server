#include <iostream>
#include <string>
#include <unordered_map>

class Utills
{

    static std::string getValueFromMap(std::unordered_map<std::string, std::string> map, std::string key, std::string defaultValue)
    {
        auto value = map.find(key);
        if (value != map.end())
        {
            return value->second;
        }
        return defaultValue;
    }
};
