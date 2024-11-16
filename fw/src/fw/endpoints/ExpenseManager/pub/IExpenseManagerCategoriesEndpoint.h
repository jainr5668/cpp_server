#pragma once
#include "BaseEndpoint.h"

namespace endpoints
{
    namespace ExpenseManager
    {
        class IExpenseManagerCategoriesEndpoint : public BaseEndpoint
        {
        public:
            virtual void getCategories(RouteContext routeContext) = 0;
            virtual void addCategory(RouteContext routeContext) = 0;
            virtual void updateCategory(RouteContext routeContext) = 0;
            virtual void deleteCategory(RouteContext routeContext) = 0;
        };
    }
}





DEFINE_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerCategoriesEndpoint, "852728487")