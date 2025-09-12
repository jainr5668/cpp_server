#pragma once
#include <nlohmann/json.hpp>
#include <boost/optional.hpp>
#include <iostream>

namespace Example
{
    class JsonType
    {
    public:

        /**
         * @brief Default constructor
         * 
         */
        JsonType()
        {
            jsonObject = nlohmann::json::object();
        }

        /**
         * @brief Resets the jsonObject
         * 
         */
        void reset()
        {
            jsonObject.clear();
        }

        /**
         * @brief Sets the value in the jsonObject
         * 
         * @tparam T Type of the value
         * @param key Key to set the value
         * @param value Value to set
         */
        template <typename T>
        void setValue(const std::string &key, const T &value)
        {
            if constexpr (std::is_base_of<JsonType, T>::value)
            {
                jsonObject[key] = value.getJsonObject();
            }
            else
            {
                jsonObject[key] = value;
            }
        }

        /**
         * @brief Gets the value from the jsonObject
         * 
         * @tparam T Type of the value
         * @param key Key to get the value
         * @return boost::optional<T> Value of the key
         */
        template <typename T>
        boost::optional<T> getValue(const std::string &key) const
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

        /**
         * @brief Sets the jsonObject
         * 
         * @param jsonObject nlohmann::json
         */
        void setJsonObject(const nlohmann::json &jsonObject)
        {
            this->jsonObject = jsonObject;
        }

        /**
         * @brief Gets the jsonObject
         * 
         * @return nlohmann::json
         */
        nlohmann::json getJsonObject() const
        {
            return jsonObject;
        }

        /**
         * @brief Removes the key from the jsonObject
         * 
         * @param key std::string
         */
        void removeKey(const std::string &key)
        {
            if (jsonObject.contains(key))
            {
                jsonObject.erase(key);
            }
        }

        /**
         * @brief Checks if the jsonObject contains the key
         * 
         * @param key std::string
         * @return true if the key exists
         * @return false if the key does not exist
         */
        bool containsKey(const std::string &key) const
        {
            return jsonObject.contains(key);
        }

        /**
         * @brief Converts the jsonObject to a string
         * 
         * @param intend int
         * @return std::string
         */
        std::string toString(int intend = -1) const
        {
            return jsonObject.dump(intend);
        }

        /**
         * @brief Parses the JSON string and sets the jsonObject
         * 
         * @param jsonString std::string
         */
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

        /**
         * @brief Builds the object from a JSON string
         * 
         * @param value std::string
         */
        void build(const std::string &value)
        {
            if (value.empty())
            {
                setJsonObject(nlohmann::json::parse("{}"));
            }
            else
            {
                setJsonObject(nlohmann::json::parse(value));
            }
        }

        /**
         * @brief Builds the object from a JSON object
         * 
         * @param value nlohmann::json
         */
        void build(const nlohmann::json &value)
        {
            setJsonObject(value);
        }

    private:
        nlohmann::json jsonObject;
    };
}