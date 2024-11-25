#ifndef AUTHENTICATIONSERVICEINJECTIONS_H
#define AUTHENTICATIONSERVICEINJECTIONS_H
#include "AuthenticationServiceData.h"
#include <memory>
#include "IUtilityService.h"

namespace services
{
    namespace AuthenticationService
    {
        class AuthenticationServiceInjections
        {
        public:
            std::unique_ptr<AuthenticationServiceData> authenticationServiceData_{nullptr};
            std::shared_ptr<services::CommonService::IUtilityService> utilityService{nullptr};
        };
    } // namespace services::AuthenticationServiceData
} // namespace services
#endif // AUTHENTICATIONSERVICEINJECTIONS_H