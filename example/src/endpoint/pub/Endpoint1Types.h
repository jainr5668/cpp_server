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

            /**
             * @brief Default constructor
             * 
             */
            Endpoint1Request() = default;

            /**
             * @brief Constructor with JSON string
             * 
             * @param jsonString JSON string
             */
            Endpoint1Request(const std::string &jsonString)
            {
                fromString(jsonString);
            }

            /**
             * @brief Constructor with JSON object
             * 
             * @param jsonObject JSON object
             */
            Endpoint1Request(const nlohmann::json &jsonObject)
            {
                setJsonObject(jsonObject);
            }

            /**
             * @brief Gets the name from the JSON object
             * @return boost::optional<std::string> Name
             */
            boost::optional<std::string> getName() const
            {
                return getValue<std::string>("name");
            }

            /**
             * @brief Sets the name in the JSON object
             * 
             * @param name Name to set
             */
            void setName(const std::string &name)
            {
                setValue<std::string>("name", name);
            }

            /**
             * @brief Removes the name from the JSON object
             * 
             */
            void removeName()
            {
                removeKey("name");
            }
            /**
             * @brief Gets the description from the JSON object
             * 
             * @return boost::optional<std::string> Description
             */
            boost::optional<std::string> getDescription()
            {
                return getValue<std::string>("description");
            }

            /**
             * @brief Sets the description in the JSON object
             * 
             * @param description Description to set
             */
            void setDescription(const std::string &description)
            {
                setValue<std::string>("description", description);
            }

            /**
             * @brief Removes the description from the JSON object
             * 
             */
            void removeDescription()
            {
                removeKey("description");
            }

            /**
             * @brief Gets the type from the JSON object
             * 
             * @return boost::optional<std::string> Type
             */
            boost::optional<std::string> getType()
            {
                return getValue<std::string>("type");
            }

            /**
             * @brief Sets the type in the JSON object
             * 
             * @param type Type to set
             */
            void setType(const std::string &type)
            {
                setValue<std::string>("type", type);
            }

            /**
             * @brief Removes the type from the JSON object
             * 
             */
            void removeType()
            {
                removeKey("type");
            }

            /**
             * @brief Gets the status from the JSON object
             * 
             * @return boost::optional<std::string> Status
             */
            boost::optional<std::string> getStatus()
            {
                return getValue<std::string>("status");
            }

            /**
             * @brief Sets the status in the JSON object
             * 
             * @param status Status to set
             */
            void setStatus(const std::string &status)
            {
                setValue<std::string>("status", status);
            }

            /**
             * @brief Removes the status from the JSON object
             * 
             */
            void removeStatus()
            {
                removeKey("status");
            }

            /**
             * @brief Gets the id from the JSON object
             * 
             * @return boost::optional<int> Id
             */
            boost::optional<int> getId() const
            {
                return getValue<int>("id");
            }

            /**
             * @brief Sets the id in the JSON object
             * 
             * @param id Id to set
             */
            void setId(const int &id)
            {
                setValue<int>("id", id);
            }

            /**
             * @brief Removes the id from the JSON object
             * 
             */
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
            void buildEndpoint1Request(Endpoint1Request *endpoint1Request = new Endpoint1Request())
            {
                setEndpoint1Request(*endpoint1Request);
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