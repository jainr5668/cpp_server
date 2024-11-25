#ifndef IEXPENSEMANAGERREPORTSENDPOINT_H
#define IEXPENSEMANAGERREPORTSENDPOINT_H
#include "BaseEndpoint.h"

namespace endpoints{
    namespace ExpenseManager{
        class IExpenseManagerReportsEndpoint : public BaseEndpoint{
            virtual void addReport(RouteContext routeContext) = 0;
            virtual void getReport(RouteContext routeContext) = 0;
            virtual void deleteReport(RouteContext routeContext) = 0;
            virtual void getReports(RouteContext routeContext) = 0;
            virtual void updateReport(RouteContext routeContext) = 0;
        };
    }
}
DEFINE_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerReportsEndpoint, "852728488")
#endif // IEXPENSEMANAGERREPORTSENDPOINT_H
