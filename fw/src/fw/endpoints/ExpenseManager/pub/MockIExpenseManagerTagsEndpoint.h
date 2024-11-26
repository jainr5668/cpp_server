#ifndef MOCKIEXPENSEMANAGERTAGSENDPOINT_H
#define MOCKIEXPENSEMANAGERTAGSENDPOINT_H
#include "IExpenseManagerTagsEndpoint.h"
#include <gmock/gmock.h>
namespace endpoints{
    namespace ExpenseManager{
        class MockIExpenseManagerTagsEndpoint : public IExpenseManagerTagsEndpoint{
        public:
        MOCK_METHOD1(addTag, void(RouteContext routeContext));
        MOCK_METHOD1(getTag, void(RouteContext routeContext));
        MOCK_METHOD1(deleteTag, void(RouteContext routeContext));
        MOCK_METHOD1(getTags, void(RouteContext routeContext));
        MOCK_METHOD1(updateTag, void(RouteContext routeContext));
        };
    }
}
#endif // MOCKIEXPENSEMANAGERTAGSENDPOINT_H