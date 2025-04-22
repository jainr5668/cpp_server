#pragma once
#include <nlohmann/json.hpp>
#include <boost/optional.hpp>
#include <iostream>

namespace Example
{
    class JsonType
    {
    public:
        JsonType()
        {
            jsonObject = nlohmann::json::object();
        }
        void reset()
        {
            jsonObject.clear();
        }
        template <typename T>
        void setValue(const std::string &key, const T &value)
        {
            if constexpr (std::is_base_of<JsonType, T>::value)
            {
                // If T is derived from JsonType, use its internal JSON object
                jsonObject[key] = value.getJsonObject();
            }
            else
            {
                // Otherwise, assign the value directly
                jsonObject[key] = value;
            }
        }
        template <typename T>
        boost::optional<T> getValue(const std::string &key)
        {
            boost::optional<T> result = boost::none;
            if (!jsonObject.contains(key))
            {
                return result;
            }
            if constexpr (std::is_base_of<JsonType, T>::value)
            {
                result = T();
                result.value().setJsonObject(jsonObject.at(key));
            }
            else
            {
                result = jsonObject.at(key).get<T>();
            }
            return result;
        }
        void setJsonObject(const nlohmann::json &jsonObject)
        {
            this->jsonObject = jsonObject;
        }
        nlohmann::json getJsonObject() const
        {
            return jsonObject;
        }
        void removeKey(const std::string &key)
        {
            if (jsonObject.contains(key))
            {
                jsonObject.erase(key);
            }
        }
        bool containsKey(const std::string &key) const
        {
            return jsonObject.contains(key);
        }
        std::string toString(int intend = -1) const
        {
            return jsonObject.dump(intend);
        }
        void fromString(const std::string &jsonString)
        {
            try
            {
                jsonObject = nlohmann::json::parse(jsonString);
            }
            catch (const std::exception &e)
            {
                throw std::runtime_error("Failed to parse JSON string: " + std::string(e.what()));
            }
        }
        void build(const std::string &value)
        {
            setJsonObject(nlohmann::json::parse(value));
        }
        void build(const nlohmann::json &value)
        {
            setJsonObject(value);
        }
        // JsonType &operator=(const nlohmann::json &other)
        // {
        //     jsonObject = other;
        //     return *this;
        // }

    private:
        nlohmann::json jsonObject;
    };
}