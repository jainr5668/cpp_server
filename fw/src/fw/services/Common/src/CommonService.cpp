#include "CommonService.h"
#include <iostream>
#include <random>
// #include "BaseService.h"

namespace services
{
    namespace CommonService
    {
        CommonService::CommonService()
        {
            logger_.info("CommonService::CommonService Entry");
            std::random_device rd;
            std::mt19937 gen(rd());

            // Define the distribution range for the random integer
            std::uniform_int_distribution<> dis(1, 100); // Range from 1 to 100

            // Generate a random integer
            int random_int = dis(gen);
            a = random_int;
            logger_.info("CommonService::CommonService Exit");
        }

        CommonService::~CommonService()
        {
            logger_.info("CommonService::~CommonService Entry");
            logger_.info("CommonService::~CommonService Exit");
        }

        void CommonService::initialize()
        {
            logger_.info("CommonService::initialize Entry");
            injections_ = new services::CommonService::CommonServiceInjections();
            injections_->utilityService = std::make_shared<services::CommonService::UtilityService>();
            logger_.info("CommonService::initialize Exit");
        }

        void *CommonService::getInterface(ModuleUid uid)
        {
            logger_.info("CommonService::getInterface Entry");
            void *interface = nullptr;
            if (uid == GET_MODULE_UID(services::CommonService::IUtilityService))
            {
                interface = injections_->utilityService.get();
            }
            else if(uid == GET_MODULE_UID(services::CommonService::ICommonService))
            {
                interface = this;
            }
            logger_.info("CommonService::getInterface Exit");
            return interface;
        }

        void CommonService::setInterface(ModuleUid uid, void *interface)
        {
            logger_.info("CommonService::setInterface Entry");
            logger_.info("CommonService::setInterface Exit");
        }

        void CommonService::connect()
        {
            logger_.info("CommonService::connect Entry");
            logger_.info("CommonService::connect Exit");
        }

        void *CommonService::getInstance()
        {
            logger_.info("CommonService::getInstance Entry");
            logger_.info("CommonService::getInstance Exit");
            return this;
        }

        void CommonService::shutdown()
        {
            logger_.info("CommonService::shutdown Entry");
            logger_.info("CommonService::shutdown Exit");
        }

        ModuleUid CommonService::getInterfaceUID()
        {
            logger_.info("CommonService::getInterfaceUID Entry");
            logger_.info("CommonService::getInterfaceUID Exit");
            return GET_MODULE_UID(services::CommonService::ICommonService);
        }
    }
}
