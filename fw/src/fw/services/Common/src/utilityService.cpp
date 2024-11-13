#include "UtilityService.h"
#include "BaseService.h"

namespace services{
    namespace CommonService{
        UtilityService::UtilityService()
        {
            logger_.info("UtilityService::UtilityService Entry");
            logger_.info("UtilityService::UtilityService Exit");
        }

        UtilityService::~UtilityService()
        {
            logger_.info("UtilityService::~UtilityService Entry");
            logger_.info("UtilityService::~UtilityService Exit");
        }

        void UtilityService::initialize()
        {
            logger_.info("UtilityService::initialize Entry");
            logger_.info("UtilityService::initialize Exit");
        }

        void *UtilityService::getInterface(ModuleUid uid)
        {
            logger_.info("UtilityService::getInterface Entry");
            logger_.info("UtilityService::getInterface Exit");
            return nullptr;
        }

        void UtilityService::setInterface(ModuleUid uid, void *interface)
        {
            logger_.info("UtilityService::setInterface Entry");
            logger_.info("UtilityService::setInterface Exit");
        }

        void UtilityService::connect()
        {
            logger_.info("UtilityService::connect Entry");
            logger_.info("UtilityService::connect Exit");
        }

        void *UtilityService::getInstance()
        {
            logger_.info("UtilityService::getInstance Entry");
            logger_.info("UtilityService::getInstance Exit");
            return this;
        }

        void UtilityService::shutdown()
        {
            logger_.info("UtilityService::shutdown Entry");
            logger_.info("UtilityService::shutdown Exit");
        }

        ModuleUid UtilityService::getInterfaceUID()
        {
            return GET_MODULE_UID(services::CommonService::IUtilityService);
        }

        std::string UtilityService::getValueFromMap(std::unordered_map<std::string, std::string> map, std::string key, std::string defaultValue)
        {
            logger_.info("UtilityService::getValueFromMap Entry");
            std::string returnValue;
            auto value = map.find(key);
            if (value != map.end())
            {
                returnValue = value->second;
            }
            else
            {
                returnValue = defaultValue;
            }
            logger_.info("UtilityService::getValueFromMap Exit");
            return returnValue;
        }

        std::string UtilityService::get_uuid()
        {
            logger_.info("UtilityService::get_uuid Entry");
            boost::uuids::uuid uuid = boost::uuids::random_generator()();
            logger_.info("UtilityService::get_uuid Exit");
            return boost::uuids::to_string(uuid);
        }

        std::string UtilityService::timepoint_to_string(const std::chrono::system_clock::time_point &tp, std::string dtFormat)
        {
            logger_.info("UtilityService::timepoint_to_string Entry");
            auto time = std::chrono::system_clock::to_time_t(tp);
            std::stringstream ss;
            ss << std::put_time(std::localtime(&time), dtFormat.c_str());
            logger_.info("UtilityService::timepoint_to_string Exit");
            return ss.str();
        }

        std::chrono::system_clock::time_point UtilityService::string_to_timepoint(const std::string &str, std::string dtFormat)
        {
            logger_.info("UtilityService::string_to_timepoint Entry");
            std::tm tm = {};
            std::stringstream ss(str);
            ss >> std::get_time(&tm, dtFormat.c_str());
            logger_.info("UtilityService::string_to_timepoint Exit");
            return std::chrono::system_clock::from_time_t(std::mktime(&tm));
        }

        nlohmann::json UtilityService::string_to_json(const std::string &str)
        {
            logger_.info("UtilityService::string_to_json Entry");
            logger_.info("UtilityService::string_to_json Exit");
            return nlohmann::json::parse(str);
        }

        std::vector<std::string> UtilityService::splitByStream(const std::string &str, char delimiter)
        {
            logger_.info("UtilityService::splitByStream Entry");
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream tokenStream(str);
            while (std::getline(tokenStream, token, delimiter))
            {
                tokens.push_back(token);
            }
            logger_.info("UtilityService::splitByStream Exit");
            return tokens;
        }
    }
}