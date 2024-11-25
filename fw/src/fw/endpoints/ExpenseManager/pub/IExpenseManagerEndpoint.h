#ifndef IEXPENSEMANAGERENDPOINT_H
#define IEXPENSEMANAGERENDPOINT_H
#include "BaseEndpoint.h"

namespace endpoints{
    namespace ExpenseManager{
        class IExpenseManagerEndpoint : public BaseEndpoint{};
    }
}
DEFINE_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerEndpoint, "2174221216")
#endif // IEXPENSEMANAGERENDPOINT_H