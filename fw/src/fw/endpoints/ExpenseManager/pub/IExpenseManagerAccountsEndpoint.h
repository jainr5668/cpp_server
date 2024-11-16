#pragma once
#include "BaseEndpoint.h"

namespace endpoints{
    namespace ExpenseManager{
        class IExpenseManagerAccountsEndpoint : public BaseEndpoint{
            virtual void addAccount(RouteContext routeContext) = 0;
            virtual void getAccount(RouteContext routeContext) = 0;
            virtual void deleteAccount(RouteContext routeContext) = 0;
            virtual void getAccounts(RouteContext routeContext) = 0;
            virtual void updateAccount(RouteContext routeContext) = 0;
        };
    }
}





DEFINE_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerAccountsEndpoint, "852728486")