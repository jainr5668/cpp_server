#pragma once
#include "BaseEndpoint.h"

namespace endpoints{
    namespace ExpenseManager{
        class IExpenseManagerTransationsEndpoint : public BaseEndpoint{
            virtual void addTransation(RouteContext routeContext) = 0;
            virtual void getTransation(RouteContext routeContext) = 0;
            virtual void deleteTransation(RouteContext routeContext) = 0;
            virtual void getTransations(RouteContext routeContext) = 0;
            virtual void updateTransation(RouteContext routeContext) = 0;
        };
    }
}









DEFINE_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerTransationsEndpoint, "852728488")