#pragma once
#include "BaseEndpoint.h"

namespace endpoints{
    namespace ExpenseManager{
        class IExpenseManagerTagsEndpoint : public BaseEndpoint{
            virtual void addTag(RouteContext routeContext) = 0;
            virtual void getTag(RouteContext routeContext) = 0;
            virtual void deleteTag(RouteContext routeContext) = 0;
            virtual void getTags(RouteContext routeContext) = 0;
            virtual void updateTag(RouteContext routeContext) = 0;
        };
    }
}










DEFINE_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerTagsEndpoint, "852728486")