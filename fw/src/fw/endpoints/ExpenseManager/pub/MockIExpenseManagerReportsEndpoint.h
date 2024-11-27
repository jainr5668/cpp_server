#ifndef MOCKIEXPENSEMANAGERREPORTSENDPOINT_H
#define MOCKIEXPENSEMANAGERREPORTSENDPOINT_H
#include "IExpenseManagerReportsEndpoint.h"
#include <gmock/gmock.h>
namespace endpoints
{
    namespace ExpenseManager
    {
        class MockIExpenseManagerReportsEndpoint : public IExpenseManagerReportsEndpoint
        {
        public:
        MOCK_METHOD1(addReport, void(RouteContext routeContext));
        MOCK_METHOD1(getReport, void(RouteContext routeContext));
        MOCK_METHOD1(deleteReport, void(RouteContext routeContext));
        MOCK_METHOD1(getReports, void(RouteContext routeContext));
        MOCK_METHOD1(updateReport, void(RouteContext routeContext));
        };
    } // namespace endpoints::ExpenseManager
} // namespace endpoints
#endif // MOCKIEXPENSEMANAGERREPORTSENDPOINT_H
