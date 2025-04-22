#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <boost/optional.hpp>

#include "jsonType.h"

namespace Example
{
    namespace Endpoint
    {
        class Endpoint1Request : public JsonType
        {
        private:
        public:
            Endpoint1Request()=default;
            Endpoint1Request(const std::string &jsonString)
            {
                fromString(jsonString);
            }
            Endpoint1Request(const nlohmann::json &jsonObject)
            {
                setJsonObject(jsonObject);
            }
            boost::optional<std::string> getName()
            {
                return getValue<std::string>("name");
            }
            void setName(const std::string &name)
            {
                setValue<std::string>("name", name);
            }
            void removeName()
            {
                removeKey("name");
            }
            boost::optional<std::string> getDescription()
            {
                return getValue<std::string>("description");
            }
            void setDescription(const std::string &description)
            {
                setValue<std::string>("description", description);
            }
            void removeDescription()
            {
                removeKey("description");
            }
            boost::optional<std::string> getType()
            {
                return getValue<std::string>("type");
            }
            void setType(const std::string &type)
            {
                setValue<std::string>("type", type);
            }
            void removeType()
            {
                removeKey("type");
            }
            boost::optional<std::string> getStatus()
            {
                return getValue<std::string>("status");
            }
            void setStatus(const std::string &status)
            {
                setValue<std::string>("status", status);
            }
            void removeStatus()
            {
                removeKey("status");
            }
            boost::optional<int> getId()
            {
                return getValue<int>("id");
            }
            void setId(const int &id)
            {
                setValue<int>("id", id);
            }
            void removeId()
            {
                removeKey("id");
            }
        };

        class Endpoint1Response : public JsonType
        {
            public:
            boost::optional<Endpoint1Request> getEndpoint1Request()
            {
                return getValue<Endpoint1Request>("endpoint1Request");
            }
            void setEndpoint1Request(const Endpoint1Request &endpoint1Request)
            {
                setValue<Endpoint1Request>("endpoint1Request", endpoint1Request);
            }
            void removeEndpoint1Request()
            {
                removeKey("endpoint1Request");
            }
            boost::optional<std::string> getMessage()
            {
                return getValue<std::string>("message");
            }
            void setMessage(const std::string &message)
            {
                setValue<std::string>("message", message);
            }
            void removeMessage()
            {
                removeKey("message");
            }
        };
    } // namespace Endpoint
} // namespace Example