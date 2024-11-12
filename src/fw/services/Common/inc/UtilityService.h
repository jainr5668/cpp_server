#pragma once

#include "IUtilityService.h"
#include "logger.h"

namespace services
{
    namespace CommonService
    {
        class UtilityService : public IUtilityService
        {
        public:
            UtilityService();
            ~UtilityService();
            void initialize() override;
            void *getInterface(ModuleUid uid) override;
            void setInterface(ModuleUid uid, void *interface) override;
            void connect() override;
            void *getInstance() override;
            void shutdown() override;
            ModuleUid getInterfaceUID() override;

            std::string getValueFromMap(std::unordered_map<std::string, std::string> map, std::string key, std::string defaultValue) override;
            std::string get_uuid() override;
            std::string timepoint_to_string(const std::chrono::system_clock::time_point &tp, std::string dtFormat = "%Y-%m-%dT%H:%M:%S") override;
            std::chrono::system_clock::time_point string_to_timepoint(const std::string &str, std::string dtFormat = "%Y-%m-%dT%H:%M:%S") override;
            nlohmann::json string_to_json(const std::string &str) override;
            std::vector<std::string> splitByStream(const std::string &str, char delimiter = ' ') override;

        private:
            Logger logger_;
        };
    }
}