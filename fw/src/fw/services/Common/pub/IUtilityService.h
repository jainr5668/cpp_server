#ifndef IUTILITYSERVICE_H
#define IUTILITYSERVICE_H
#include "BaseService.h"
#include <unordered_map>
#include <string>
#include <chrono>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace services
{
    namespace CommonService
    {
        class IUtilityService : public BaseService
        {
        public:
            virtual void initialize() = 0;
            virtual void *getInterface(ModuleUid uid) = 0;
            virtual void setInterface(ModuleUid uid, void *interface) = 0;
            virtual void connect() = 0;
            virtual void *getInstance() = 0;
            virtual void shutdown() = 0;
            virtual ModuleUid getInterfaceUID() = 0;
            virtual ~IUtilityService() = default;

            /**
             * Get value from map if key exists, otherwise return default value
             */
            virtual std::string getValueFromMap(std::unordered_map<std::string, std::string> map, std::string key, std::string defaultValue) = 0;
            /**
             * Generate UUID
             */
            virtual std::string get_uuid() = 0;

            /**
             * Convert time_point to string
             */
            virtual std::string timepoint_to_string(const std::chrono::system_clock::time_point &tp, std::string dtFormat = "%Y-%m-%dT%H:%M:%S") = 0;

            /**
             * Convert string to time_point
             */
            virtual std::chrono::system_clock::time_point string_to_timepoint(const std::string &str, std::string dtFormat = "%Y-%m-%dT%H:%M:%S") = 0;

            /**
             * String to unordered_map
             */
            virtual nlohmann::json string_to_json(const std::string &str) = 0;

            /**
             * string to vector
             */
            virtual std::vector<std::string> splitByStream(const std::string &str, char delimiter = ' ') = 0;
        };
    }
}
DEFINE_MODULE_UID(services::CommonService::IUtilityService, "0x00000023")
#endif // IUTILITYSERVICE_H