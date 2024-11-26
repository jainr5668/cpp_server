#ifndef MOCKIUTILITYSERVICE_H
#define MOCKIUTILITYSERVICE_H
#include "IUtilityService.h"
#include <gmock/gmock.h>
namespace services
{
    namespace CommonService
    {
        class MockIUtilityService : public IUtilityService
        {
        public:
            MOCK_METHOD0(initialize, void());
            MOCK_METHOD1(getInterface, void*(ModuleUid uid));
            MOCK_METHOD2(setInterface, void(ModuleUid uid, void *interface));
            MOCK_METHOD0(connect, void());
            MOCK_METHOD0(getInstance, void*());
            MOCK_METHOD0(shutdown, void());
            MOCK_METHOD0(getInterfaceUID, ModuleUid());
            MOCK_METHOD3(getValueFromMap, std::string(std::unordered_map<std::string, std::string> map, std::string key, std::string defaultValue));
            MOCK_METHOD0(get_uuid, std::string());
            MOCK_METHOD2(timepoint_to_string, std::string(const std::chrono::system_clock::time_point &tp, std::string dtFormat));
            MOCK_METHOD2(string_to_timepoint, std::chrono::system_clock::time_point(const std::string &str, std::string dtFormat));
            MOCK_METHOD1(string_to_json, nlohmann::json(const std::string &str));
            MOCK_METHOD2(splitByStream, std::vector<std::string>(const std::string &str, char delimiter));
        };
    }
}
#endif // MOCKIUTILITYSERVICE_H